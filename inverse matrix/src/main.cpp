#include <iostream>
#include <time.h>
#include "matrix.h"
using namespace std;


int main() {
/*
	int m;
	int n;
	cout << "Enter the matrix size (n x n) :\n";
	cin >> n;
	cout << "Enter the accuracy parameter (integer) :\n";
	cin >> m;
	cout << "Enter the matrix :\n";*/
	
	int n = 2048;
	int m = 10;
	
	Matrix aMat(n);
	aMat.entry_arr();

	timespec start, end;
	if (timespec_get(&start, TIME_UTC) != -1);
	Matrix inverseA = inverse_matrix(aMat, m);
	if(timespec_get(&end, TIME_UTC)!= -1);

	cout << "----------------------------------------" << endl;
	inverseA.print_matrix();
	cout << "----------------------------------------\n\n\n";
	cout << "Calculation time: " << (end.tv_sec - start.tv_sec) + 0.000000001 * (end.tv_nsec - start.tv_nsec) << "sec. ";

	return 0;
}
