#pragma once
class Matrix {
public:
	Matrix();
	Matrix(int size);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) noexcept;

	void entry_arr();
	void print_matrix() const;
	int get_size() const;

	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other) noexcept;
	friend Matrix operator+(const Matrix&, const Matrix&);
	friend Matrix operator-(const Matrix&, const Matrix&);
	friend Matrix transp_mat(const Matrix&);
	friend Matrix operator*(const Matrix&, const float);
	friend Matrix operator*(const Matrix&, const Matrix&);
	friend float find_max_row(const Matrix&);
	void make_one();
	void make_zero();

	float* begin() const;
	float* end() const;

	~Matrix();
private:
	int n; //размерность квадратной матрицы
	float* mat; //сама матрица записанна в одномерный массив строка за строкой
};

Matrix inverse_matrix(const Matrix&, const int);
