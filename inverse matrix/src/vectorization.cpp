#include "matrix.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Matrix::Matrix() : n(0), mat(nullptr) {}
Matrix::Matrix(int size) : n(size) { mat = new float[1ll * size * size]; }
Matrix::Matrix(const Matrix& other) : n(other.n) {  // заменить other.n на n
	mat = new float[1ll * other.n * other.n];
	for (int i = 0; i < other.n; i++)
		for (int j = 0; j < other.n; j++)
			mat[i * other.n + j] = other.mat[i * other.n + j];
}
Matrix::Matrix(Matrix&& other) noexcept : n(move(other.n)) {
	mat = other.mat;
	other.mat = nullptr;
}

void Matrix::entry_arr() {
	string strmat;
	cin.get();
	for (int i = 0; i < n; i++) {
		getline(cin, strmat);
		int k = 0;
		int begin = 0;
		int length = 0;
		for (int j = 0; j < strmat.size(); j++) { //заполнение строк матрицы
			if (strmat[j] == ' ' || j == strmat.size() - 1) {
				mat[i * n + k] = atof((strmat.substr(begin, length)).c_str());
				begin = j + 1;
				length = 1;
				k++;
			}
			else {
				length++;
			}
		}
	}
}
void Matrix::print_matrix() const {
	int size = n * n;
	for (int i = 0; i < size; i++) {
		cout << setw(11) << mat[i] << ' ';
		if ((i + 1) % n == 0 && i != 0)
			cout << '\n';
	}
}
int Matrix::get_size() const { return n; }

Matrix& Matrix::operator=(const Matrix& other) {
	if (this != &other) {
		n = other.n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				mat[i * n + j] = other.mat[i * n + j];
	}
	return *this;
}
Matrix& Matrix::operator=(Matrix&& other) noexcept {
	if (this != &other) {
		n = move(n);
		mat = other.mat;
		other.mat = nullptr;
	}
	return *this;
}

void Matrix::make_one() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat[i * n + j] = (i == j);
}
void Matrix::make_zero() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			mat[i * n + j] = 0;
}

float* Matrix::begin() const { return mat; }
float* Matrix::end() const { return mat + 1ll * n * n; }

Matrix::~Matrix() { delete[] mat; }

Matrix operator+(const Matrix& a, const Matrix& b) {
	int n = a.n;
	Matrix temp(n);
	float* aptr = a.mat;
	float* bptr = b.mat;
	float* tempptr = temp.mat;
	for(int i = 0; i < n*n/8; i++){
		asm volatile("movq %0, %%rax" :: "m"(aptr));
		asm volatile("movq %0, %%rbx" :: "m"(bptr));
		asm volatile("movq %0, %%rsi" :: "m"(tempptr));
		asm volatile("vmovups (%rax), %ymm0");
		asm volatile("vmovups (%rbx), %ymm1");
		asm volatile("vaddps %ymm1, %ymm0, %ymm3");
		asm volatile("vmovups %ymm0, (%rsi)");
		aptr += 8;
		bptr += 8;
		tempptr += 8;
	}

	/*
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp.mat[i * n + j] = a.mat[i * n + j] + b.mat[i * n + j];
	*/
	return temp;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
	int n = a.n;
	Matrix temp(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp.mat[i * n + j] = a.mat[i * n + j] - b.mat[i * n + j];
	return temp;
}

Matrix transp_mat(const Matrix& a) {
	int n = a.n;
	Matrix tranps(a);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tranps.mat[i * n + j] = a.mat[j * n + i];
	return tranps;
}

Matrix operator*(const Matrix& a, const float scal) {
	int n = a.n;
	Matrix temp(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp.mat[i * n + j] = a.mat[i * n + j] * scal;
	return temp;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
	int n = b.n;
	Matrix temp(n);
	temp.make_zero();

	/*
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				temp.mat[i * n + j] += a.mat[i * n + k] * b.mat[k * n + j];*/

	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < n; ++k) {
#pragma omp simd
			for (int j = 0; j < n; ++j) {
				temp.mat[i * n + j] += a.mat[i * n + k] * b.mat[k * n + j];
			}
		}
	}

	return temp;
}

float find_max_row(const Matrix& m) {
	float a_row = 0;
	float sum_row = 0;
	size_t size = 1ll * m.n * m.n;
	for (size_t i = 0; i < size; i++) {
		if (i % m.n == 0) {
			if (sum_row > a_row) {
				a_row = sum_row;
			}
			sum_row = m.mat[i];
		}
		else {
			sum_row += m.mat[i];
		}
	}
	if (sum_row > a_row)
		a_row = sum_row;
	return a_row;
}

Matrix inverse_matrix(const Matrix& aMat, const int m) {
	int n = aMat.get_size();
	Matrix rMat(n);
	Matrix bMat(n);
	Matrix oneMat(n);
	oneMat.make_one();

	float max_sum_row = find_max_row(aMat);
	float max_sum_col = find_max_row(transp_mat(aMat));
	bMat = transp_mat(aMat) * ((1.0 / max_sum_row) * (1.0 / max_sum_col));
	rMat = oneMat - (bMat * aMat);

	Matrix sum_degree_r(n);
	Matrix degree_r = rMat;
	sum_degree_r.make_one();
	if (m >= 2)
		for (int i = 1; i < m; i++) {
			sum_degree_r = sum_degree_r + degree_r;
			degree_r = degree_r * rMat;
		}

	return sum_degree_r * bMat;
}
