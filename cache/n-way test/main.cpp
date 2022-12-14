#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <limits.h>
#include <fstream>
#include <Intrin.h>
using namespace std;


void print(int* arr, const int nfragments, const int fragsize) {
	int j = 0;
	for (int i = 0; i < nfragments * fragsize; i++) {
		std::cout << nfragments << ' ' << fragsize << " : " << j << " - " << arr[j] << '\n';
		j = arr[j];
	}
}

unsigned long long min_arr(const unsigned long long* arr, const int size) {
	unsigned long long min = ULLONG_MAX;
	for (int i = 0; i < size; i++) {
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}

void init(int* arr, const int nfragments, const int offset, const int fragsize) {
	// для каждого из fragsize-1 элементов ставим индекс соответсвующего элемента
	// из следующего фрагмента (отличающегося на +offset)
	for (int i = 0; i < fragsize-1; i++) {
		int position = i;							
		for (int j = 0; j < nfragments-1; j++) {
			arr[position] = position + offset;
			position += offset;
		}
		// последний элемент направляем в следующий начальный элемент fragsize
		arr[position] = (i + 1) % fragsize;			
	}
}

int test(const int* arr, const int nfragments, const int fragsize) {
	unsigned long long start, end; // хранят начало конец времени измерения в тактах
	const int ntrav = 50;		   // число обходов 
	const int nattemps = 50;	   // количество замеров (т.е. каждый замер выполняется ntrav обходов)
	unsigned long long times[nattemps]; // массив для выбора наименьшего из замеров

	for (int k = 0; k < nattemps; k++) { // цикл по количеству замеров
		int j = 0;
		start = __rdtsc();
		// nfragments * fragsize - количество элементов в обходе
		// * ntrav - количество обходов
		for (int i = 0; i < nfragments * fragsize * ntrav; i++)
			j = arr[j];											  
		end = __rdtsc();

		if (j == 123123)
			printf("Ok?");

		times[k] = end - start;
	}
	return min_arr(times, nattemps) / (1ll * nfragments  * fragsize * ntrav);
}

int main() {
	//32  kb - L1
	//256 kb - L2
	//12  mb - L3
	const int ncaches = 3;			// количество уровней кешей 
	const int cachesize[ncaches] = { 8192, 65536, 3145728 };// размеры L1-L3 в интах: (sizeof(int)*cachesize[i]) = sizeof(L_i)
	const int minfragments = 1;  
	const int maxfragments = 32;	// максимальное и минимальное количество фрагментов для тестирования

	std::ofstream outcsv; // в .csv файл будет записаны результаты измерений
	outcsv.open("cacheout.csv");
	outcsv << "Fragments;" << "Time;" << "\n";

	// выделяется массив размером с запасом для тестов всех 
	// уровней кэш-памяти
	int* arr = (int*)malloc(sizeof(int) * cachesize[ncaches-1] * (maxfragments+1));
	if (arr == NULL) {
		printf("Error while creating the arr.");
		exit(1);
	}
	// для каждого из кэшей замеряется среднее время обращения к ячейке массива
	// в зависимости от числа фрагментов
	for (int i = 0; i < ncaches; i++) {							
		for (int j = minfragments; j <= maxfragments; j++) {    
			int offset = cachesize[i];	// в качестве отступа для обращения 
										// к следующему элементу выбирается
										// число равное размеру тестируемого кэша
			const int fragsize = cachesize[i] / j;	// количество элементов во фрагменте

			init(arr, j, offset, fragsize); // заполнение массива для его последующего обхода
			outcsv << j << ';' << test(arr, j, fragsize) << '\n'; // непосредственно сам тест, 
																	 // выполняющий обход и возвращающий 
																	 // среднее время обращения к ячейке
		}
	}

	free(arr);
	outcsv.close();
	return 0;
}
