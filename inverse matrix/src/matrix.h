#pragma once
#include <iostream>

class Matrix {
public:
	Matrix();
	Matrix(const size_t size);
	Matrix(const size_t size, const char* path);
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) noexcept;

	void read_from_file(const char* path);
	void entry_arr();
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
	size_t n; //размерность квадратной матрицы
	float* mat; //сама матрица записанна в одномерный массив строка за строкой

	void read_by_stream(std::istream& stream);
};

Matrix inverse_matrix(const Matrix&, const size_t);
std::ostream& operator<<(std::ostream &os, const Matrix& matrix);
