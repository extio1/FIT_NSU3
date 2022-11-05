#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;


class Matrix {
public:
	Matrix(): n(0), mat(nullptr) {}
	Matrix(int size) : n(size) { mat = new float[1ll * size * size]; }
	Matrix(const Matrix& other): n(other.n) {  // заменить other.n на n
		mat = new float[1ll * other.n * other.n];
		for (int i = 0; i < other.n; i++)
			for (int j = 0; j < other.n; j++)
				mat[i * other.n + j] = other.mat[i * other.n + j];
	}
	Matrix(Matrix&& other) noexcept : n(move(other.n)) {
		mat = other.mat;
		other.mat = nullptr;
	}

	void entry_arr() {
		string strmat;
		cin.get();
		for (int i = 0; i < n; i++) {
			getline(cin, strmat);
			int k = 0;
			int begin = 0;
			int length = 0;
			for (int j = 0; j < strmat.size(); j++) { //заполнение строк матрицы
				if (strmat[j] == ' ' || j == strmat.size() - 1) {
					mat[i*n + k] = atof((strmat.substr(begin, length)).c_str());
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
	void print_matrix() const {
		int size = n * n;
		for (int i = 0; i < size; i++) {
			cout << mat[i] << ' ';
			if ((i+1) % n == 0 && i != 0)
				cout << '\n';
		}
	}
	int get_size() const { return n; }

	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			n = other.n;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					mat[i * n + j] = other.mat[i * n + j];
		}
		return *this;
	}
	Matrix& operator=(Matrix&& other) noexcept {
		if (this != &other) {
			n = move(n);
			mat = other.mat;
			other.mat = nullptr;
		}
		return *this;
	}
	friend Matrix operator+(Matrix&, Matrix&);
	friend Matrix operator-(Matrix, Matrix);
	friend Matrix transp_mat(Matrix&);
	friend Matrix operator*(Matrix, int);
	friend Matrix operator*(Matrix&, Matrix&);

	void make_one() {
		for(int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				mat[i *n + j] = (i == j);
	}
	void make_zero() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				mat[i * n + j] = 0;
	}

	float* begin() const { return mat; }
	float* end() const { return mat + 1ll*n*n; }

	~Matrix() { delete[] mat; }
private:
	int n; //размерность квадратной матрицы
	float* mat; //сама матрица записанна в одномерный массив строка за строкой
};

Matrix operator+(Matrix& a, Matrix& b) {
	int n = a.n;
	Matrix temp(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp.mat[i * n + j] = a.mat[i * n + j] + b.mat[i * n + j];
	return temp;
}

Matrix operator-(Matrix a, Matrix b) {
	int n = a.n;
	Matrix temp(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp.mat[i * n + j] = a.mat[i * n + j] - b.mat[i * n + j];
	return temp;
}

Matrix transp_mat(Matrix& a) {
	int n = a.n;
	Matrix tranps(n);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tranps.mat[i * n + j] = a.mat[j * n + i];
	return tranps;
}

Matrix operator*(Matrix a, int scal) {
	int n = a.n;
	Matrix temp(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			temp.mat[i* n + j] *= scal;
	return temp;
}

Matrix operator*(Matrix& a, Matrix& b) {
	int n = b.n;
	Matrix temp(n);
	temp.make_zero();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				temp.mat[i * n + j] += a.mat[i * n + k] * b.mat[k * n + j];

	return temp;
}

float find_max_row(Matrix mat) {
	float a_row = 0;
	float sum_row = 0;
	int n = mat.get_size();
	int i = 1;//i указывает на позицию числа в строке (начиная с 1)
	for (float* el = mat.begin(); el < mat.end(); el++) { 
		if (i % n == 0) {
			i = 1;
			if (sum_row > a_row)
				a_row = sum_row;
			sum_row = 0;
		}
		else {
			sum_row += *el;
		}
		i++;
	}
	return a_row;
}

int main() {
	int m;
	int n;
	cout << "Enter the matrix size (n x n) :\n";
	cin >> n;
	cout << "Enter the accuracy parameter (integer) :\n";
	cin >> m;
	cout << "Enter the matrix :\n";
	Matrix aMat(n);
	aMat.entry_arr();

	Matrix rMat(n);
	Matrix bMat(n);
	Matrix oneMat(n);
	oneMat.make_one();
	//теперь все необходимые матрицы созданы

	timespec start, end;
	if (timespec_get(&start, TIME_UTC) != -1);

	float max_sum_row = find_max_row(aMat);
	float max_sum_col = find_max_row(transp_mat(aMat));

	bMat = transp_mat(aMat) * ((1 / max_sum_row) * (1 / max_sum_col));

	rMat = oneMat - bMat * aMat;
	bMat.print_matrix();

	Matrix sum_degree_r(n);
	sum_degree_r.make_zero();
	if (m >= 2){
		sum_degree_r = rMat + oneMat;
		for (int i = 2; i < m; i++) {
			rMat = rMat * rMat;
			sum_degree_r = sum_degree_r + rMat;
		}
	}
	Matrix inverseA(n);
	inverseA = sum_degree_r * bMat;
	if(timespec_get(&end, TIME_UTC != -1));

	inverseA.print_matrix();

	return 0;
}
