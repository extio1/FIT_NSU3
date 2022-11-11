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
	//cin.get();
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
	for(int i = 0; i < n*n/4; i++){
		asm volatile("movq %0, %%rax" :: "m"(aptr));
		asm volatile("movq %0, %%rbx" :: "m"(bptr));	
		asm volatile("movups (%rax), %xmm0");
		asm volatile("movups (%rbx), %xmm1");
		asm volatile("addps %xmm0, %xmm1");
		asm volatile("movq %0, %%rax" :: "m"(tempptr));
		asm volatile("movups %xmm1, (%rax)");
		aptr += 4;
		bptr += 4;
		tempptr += 4;
	}

	return temp;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
	int n = a.n;
	Matrix temp(n);
	float* aptr = a.mat;
	float* bptr = b.mat;
	float* tempptr = temp.mat;
	for(int i = 0; i < n*n/4; i++){
		asm volatile("movq %0, %%rax" :: "m"(aptr));
		asm volatile("movq %0, %%rbx" :: "m"(bptr));	
		asm volatile("movups (%rax), %xmm0");
		asm volatile("movups (%rbx), %xmm1");
		asm volatile("subps %xmm0, %xmm1");
		asm volatile("movq %0, %%rax" :: "m"(tempptr));
		asm volatile("movups %xmm1, (%rax)");
		aptr += 4;
		bptr += 4;
		tempptr += 4;
	}
	return temp;
}

Matrix transp_mat(const Matrix& a) {
	int n = a.n;
	Matrix transp(n);
	transp.make_zero();	

	for (int i = 0; i < n*n; i += 4) { //MOVLHPS
		int col = (i % n);
		int row = (i / n);
		int col_tr = row;
		int row_tr = col; //вычислили откуда начинать считывать столбец в вектор
		//std::cout << i << ' ' << row << ' ' << col << std::endl;
		float* transpptr = transp.mat + row * n + col; 		  
		float* aptr = a.mat + row_tr * n + col_tr;
		//std::cout << row << '-' << col << ' ' << row_tr << '-' << a.mat[row * n + col] <<' ';
		//std::cout << *aptr  << ' ' << *(aptr+n)  << ' ' << *(aptr + n + n)  << ' ' << *(aptr +n +n +n)  << ' ';
		//std::cout << '\n';
/*
		for(int j = 0; j < 4; j++){ //загружаем вектор xmm0 из 4 элементов столбца матрицы
			std::cout << *aptr << ' ';
			asm volatile(
				"movss %0, %%xmm0\n\t"
				//"movss %0, %%xmm1\n\t" //загружаем один элемент на 0 позицию вектора
				//"shufps $0b10010000, %%xmm1, %%xmm1\n\t" //свдиг флотов внутри на 1 позицию влево
				//"pslld %%xmm0, %%xmm1\n\t"
				"maskmovdqu %%xmm0, %%xmm1\n\t"
				:: "m"(*aptr) : "%xmm1"
			);
			aptr += n;
		}	
*/
		
		float* sec = aptr+n;
		float* tri = aptr+n+n;
		float* fou = aptr+n+n+n;
		//std::cout << *aptr << *sec << '\n';
		asm volatile(
			"movss %0, %%xmm0\n\t"
			"movss %1, %%xmm1\n\t"
			"movss %2, %%xmm2\n\t"
			"movss %3, %%xmm3\n\t"
			"punpckldq %%xmm0, %%xmm1\n\t"
			"punpckldq %%xmm2, %%xmm3\n\t"
			"punpckldq %%xmm1, %%xmm3\n\t"
			//"shufps 0b00011011, %%xmm3, %%xmm3\n\t"
			"pshufd $0b00100111, %%xmm3, %%xmm3"
			:: "m"(*aptr), "m"(*sec), "m"(*tri), "m"(*fou)
		);
/*
		float* temp = new float[4];
		asm volatile("movq %0, %%rax" :: "m"(temp));
		asm volatile("movups %xmm3, (%rax)");
		for(int k = 0; k < 4; k++)
			std::cout << temp[k] << ' ';
		std::cout << '\n';
*/
		asm volatile(
			"movq %0, %%rax\n\t"
			"movups %%xmm3, (%%rax)"
			::"m"(transpptr)
		);

		//delete [] temp;
	}

	return transp;
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
