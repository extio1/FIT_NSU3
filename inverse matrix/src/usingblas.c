#include <cblas.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int n = 2048;
const int m = 10;

float find_max_row(const float* m) {
	float a_row = 0;
	float sum_row = 0;
	size_t size = 1ll * n * n;
	for (size_t i = 0; i < size; i++) {
		if (i % n == 0) {
			if (sum_row > a_row) {
				a_row = sum_row;
			}
			sum_row = m[i];
		}
		else {
			sum_row += m[i];
		}
	}
	if (sum_row > a_row)
		a_row = sum_row;
	return a_row;
}

float find_max_col(const float* mat) {
	float a_col = 0;
	float sum_col = 0;
	size_t size = 1ll * n * n;
	
	for(int j = 0; j < n; j++){
		sum_col = 0;
		for(int i = 0; i < n; i++){
			sum_col += mat[i*n+j];
			if (sum_col > a_col) {
				a_col = sum_col;
			}
		}
	}
	
	if (sum_col > a_col)
		a_col = sum_col;
		
	return a_col;
}

void enter_matrix(float* mat){
	FILE *f = fopen("mat2048.txt", "r");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			fscanf(f, "%f", &mat[i*n+j]);
		}
	}
	fclose(f);
}

void print_matrix(const float* mat){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%f ", mat[i*n+j]);
		}
		printf("\n");
	}
}

void make_one(float* mat){
	for(int i = 0; i < n; i++){
		mat[i*n+i] = 1;
		}
}


int main(){
	const int size = n * n;
	
	float* a = (float*)malloc(sizeof(float)*n*n);
	float* b = (float*)malloc(sizeof(float)*n*n);
	float* r = (float*)malloc(sizeof(float)*n*n);
	float* sum_r = (float*)malloc(sizeof(float)*n*n);
	float* degree_r = (float*)malloc(sizeof(float)*n*n);
	float* degree_r_temp = (float*)malloc(sizeof(float)*n*n);
	struct timespec start, end;
	enter_matrix(a);
	
	
	timespec_get(&start, TIME_UTC);
	cblas_scopy(size, a, 1, b, 1); //копирует a в b. 1 - параметр, который позволяет брать каждый k-ый элемент вектора, в данном случае
				 //нужно выполнять копирование каждого элемента, поэтому тут стоит 1
	make_one(r);
	float max_col = find_max_col(a);
	float max_row = find_max_row(a);

	float alpha = 1.0/(max_col * max_row);
	cblas_sgemm(CblasRowMajor, CblasTrans, CblasNoTrans, n, n, n, alpha, a, n, r, n, 0, b, n); //вычисление B
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, -1, b, n, a, n, 1, r, n); //вычисление R
	
	make_one(sum_r);
	cblas_scopy(size, r, 1, degree_r, 1);
	if(m >= 2){
		for(int i = 1; i < m; i++){
			cblas_saxpy(size, 1.0, degree_r, 1, sum_r, 1); // sum_r = (1.0 * degree_r) +  sum_r
			cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, degree_r, n, r, n, 0.0, degree_r_temp, n); //вычисление degree_r = degree_r * r
			cblas_scopy(size, degree_r_temp, 1, degree_r, 1);						 	  //
		}
	}
	
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, sum_r, n, b, n, 0, r, n); // r = sum_r * b
	timespec_get(&end, TIME_UTC);
	
	print_matrix(r);
	printf("\nCalculation time: ");
	printf("%f sec.\n", (end.tv_sec - start.tv_sec) + 0.000000001 * (end.tv_nsec - start.tv_nsec));
	
	free(a);
	free(b);
	free(r);
	free(sum_r);
	free(degree_r);
	free(degree_r_temp);
}
