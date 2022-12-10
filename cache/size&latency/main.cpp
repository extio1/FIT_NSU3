#include <stdlib.h>
#include <stdio.h>
#include "matrix.h" //нахождение обратной матрицы - для прогрева процессора
#include <iostream>
#include <limits.h>
#include <fstream>

inline unsigned long long  get_tsc(){
	//в регистры eax и edx команда rdtsc возращает 64-битное число тактов, кладет в eax его нижнуюю часть, в edx верхнюю 
	unsigned long eax, edx;
    asm volatile("rdtsc\n\t": "=a" (eax), "=d" (edx));
    return (unsigned long long)eax | (unsigned long long)edx << 32;
}

void print(int* arr, const int size) {
	for (int i = 0; i < size; i++)
		printf("%ld ", arr[i]);
}

void direct_init(int* arr, const int size) {
	arr[size - 1] = 0;
	for (int i = 0; i < size - 1; i++) {
		arr[i] = i + 1;
	}
}

void back_init(int* arr, const int size) {
	arr[0] = size - 1;
	for (int i = size - 1; i > 0 ; i--) {
		arr[i] = i - 1;
	}
}

void warm_proc() { //работает чуть больше секунды
	Matrix warm(50);
	warm.read_from_file("mat.txt");
	inverse_matrix(warm, 3000);
}

unsigned long long min_arr(const unsigned long long* arr, const int size){
	unsigned long long min = ULLONG_MAX;
	for(int i = 0; i < size; i++){
		if(arr[i] < min)
			min = arr[i];
	}
	return min;
}

void random_init(int* arr, const int size) {
	for (int i = 0; i < size; i++) //помечаем, что ни в какие вершины еще не зашли
		arr[i] = -1;

	int cur_pos = 0;
	srand(time(NULL)); //srand задаёт параметр для генерации случайных чисел. time(NULL) возвращает текущее
					   //wall-clock время, нужное для того, чтобы в srand передавалось всегда разное значение

	unsigned long long rnd; //хранит случайное значение

	//на size-1 позицию кладется индекс еще не участвующего в обходе элемента; новый индекс отличен от текущего индекса

	for (int i = 0; i < size-1; i++) { //индекс следующего элемента случайно вычисляется
		do {
			rnd = rand() % size;
		} while (arr[rnd] != -1 || rnd == cur_pos); //выбыраем то случайное значени, которое отправляет в
													//отличную от текущей ячейку, в которую еще не заходили при обходе
		arr[cur_pos] = rnd; //в текую ячейку кладет "правильный" случайный номер следующей ячейки для обхода
		cur_pos = rnd; //двигаемся в следующую вычисленную ячейку
	}
	arr[cur_pos] = 0; //из последней ячейки в обходе обязательно идем в начало. Таким образом последовательность зациклилась
}

int test(const int* arr, const int size) {
	const int k = 5; //число повторений цикла для замера среднего времени доступа к элементу массива
	const int precision = 5; //количество повторений теста, для более точных замеров времени
	unsigned long long times[k]; //хранит несколько попыток замера времени, чтобы из них выбрать минимальную
	unsigned long long start = 0, end = 0;

	warm_proc();
	int j = 0;
	for (int i = 0; i < size; i++) { //загрузили в кэш массив. Прогрев кэша
		j = arr[j];
	}
	if (j != 0){ //цикл, проверяющий переменную из тела цикла сверху, для того, чтобы компилятор не выкидывал эту часть кода
		printf("%d", j);
	}

	for(int m = 0; m < precision; m++){
		int j = 0;

		start = get_tsc(); //возвращает текущее значени тактов
		for (int i = 0; i < size*k; i++) {
			j = arr[j];
		}
		end = get_tsc();

		if (j != 0){ //цикл, проверяющий переменную из тела цикла сверху, для того, чтобы компилятор не выкидывал эту часть кода
			printf("Ok ");
		}

		times[m] = end - start;
	}

	return min_arr(times, precision) / (size * k); //всего обращений в память n*size, 
									               //время за которое они произошли - это end - start (время в тактах процессора)
}

int main() {
	int nmin = 256; // sizeof(int) * 256 = 1Kb
	int nmax = 8388608; //sizeof(int) * 8388608 = 32Mb

	std::ofstream outcsv;
	outcsv.open("cacheout.csv");
	outcsv << "Size;" << "Direct;" << "Back;" << "Random;\n";

	int* arr = (int*)malloc(sizeof(int) * nmin);

	int n = nmin;
	while (n < nmax) {

		outcsv << sizeof(int)*n;
		outcsv << ';';
	
		direct_init(arr, n);
		outcsv << test(arr, n);
		outcsv << ';';

		back_init(arr, n);
		outcsv << test(arr, n);
		outcsv << ';';

		random_init(arr, n);
		outcsv << test(arr, n);
		outcsv << ';';

		outcsv << '\n';

		n *= 1.2;

		int* p;
		if ((p = (int*)realloc(arr, sizeof(int) * n)) != NULL) {
			arr = p;
		}
		else {
			printf("Allocation error.");
			exit(1);
		}
	}

	free(arr);
	outcsv.close();
}
