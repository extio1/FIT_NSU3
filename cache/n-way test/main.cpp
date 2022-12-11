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
	for (int i = 0; i < fragsize; i++) {
		int position = i;							// заполняем nfragments первых элементов во фрагментах с
		for (int j = 0; j < nfragments-1; j++) {	// отступом offset
			arr[position] = position + offset;
			position += offset;
		}
		arr[position] = (i + 1) % fragsize;			// последний элемент направляем в следующий начальный элемент fragsize
	}
}

void pullL1() {
	int* arr = new int[8192];
	for (int i = 0; i < 8192; i++) {
		arr[i] = (i + 1) % 8192;
	}
	int j = 0;
	for (int i = 0; i < 8192 * 2; i++) {
		j = arr[j];
	}
	if (j == 1123) {
		printf("ASDASD");
	}
	delete[] arr;
}

int test(const int* arr, const int nfragments, const int fragsize) {
	unsigned long long start, end; // хранят начало конец времени измерения в тактах
	const int ntrav = 50;		   // число обходов 
	const int nattemps = 50;	   // количество замеров (т.е. каждый замер выполняется ntrav обходов)
	unsigned long long times[nattemps]; // массив для выбора наименьшего из замеров

	pullL1();

	for (int k = 0; k < nattemps; k++) { // цикл по количеству замеров
		int j = 0;
		start = __rdtsc();

		for (int i = 0; i < nfragments * fragsize * ntrav; i++) { // nfragments * fragsize - количество элементов в обходе
			j = arr[j];											  // * ntrav - количество обходов
		}

		end = __rdtsc();

		if (j == 123123) {
			printf("Ok?");
		}
		times[k] = end - start;
	}

	return min_arr(times, nattemps) / (1ll * nfragments  * fragsize * ntrav);
}

int main() {
	//32  kb - L1
	//256 kb - L2
	//12  mb - L3
	const int ncaches = 3;			// количество уровней кешей 
	const int cachesize[ncaches] = { 8192, 65536, 3145728 }; // размеры L1-L3 в интах: (sizeof(int)*cachesize[i]) = sizeof(L_i)
	const int minfragments = 1;  
	const int maxfragments = 32;	// максимальное и минимальное количество фрагментов для тестирования

	std::ofstream outcsv; // в .csv файл будет записаны результаты измерений
	outcsv.open("cacheout.csv");
	outcsv << "Fragments;" << "Time;" << "\n";

	int* arr = (int*)malloc(sizeof(int) * cachesize[ncaches-1] * (maxfragments+1)); // выделяется массив размером с запасом для тестов всех 
																					// уровней кэш-памяти
	if (arr == NULL) {
		printf("Error while creating the arr.");
		exit(1);
	}

	for (int i = 0; i < 1; i++) {							// для каждого из кэшей замеряется среднее время обращения к ячейке массива
		for (int j = 2; j <=2; j++) {    // в зависимости от числа фрагментов
			int offset = cachesize[i];	// в качестве отступа для обращения к следующему элементу выбирается число равное размеру
										// тестируемого кэша
			const int fragsize = cachesize[i] / j;			// количество элементов во фрагменте

			init(arr, j, offset, fragsize); // заполнение массива для его последующего обхода
			//print(arr, j, fragsize);
			std::cout << j << ';' << test(arr, j, fragsize) << '\n'; // непосредственно сам тест, выполняющий обход и возвращающий
																	 // среднее время обращения к ячейке
		}
	}

	free(arr);
	outcsv.close();
	return 0;
}
