#pragma once
#include <string>
#include <vector>

class bigInt {
public:
	friend void fill_num(long long, bigInt&);
	bigInt();
	bigInt(int);
	bigInt(long long);
	bigInt(std::string);
	bigInt(const bigInt&);
	bigInt(bigInt&&) noexcept;
	~bigInt();

	bigInt operator~() const;

	bigInt& operator++();
	bigInt& operator--();
	const bigInt operator++(int);
	const bigInt operator--(int);

	bigInt& operator=(const bigInt&);
	bigInt& operator=(bigInt&&) noexcept;

	bigInt operator+() const;  // unary +
	bigInt operator-() const;  // unary -

	bigInt& operator+=(const bigInt&);
	bigInt& operator*=(const bigInt&);
	bigInt& operator-=(const bigInt&);
	bigInt& operator/=(const bigInt&);
	bigInt& operator%=(const bigInt&);
	bigInt& operator^=(const bigInt&);
	bigInt& operator&=(const bigInt&);
	bigInt& operator|=(const bigInt&);

	bool operator==(const bigInt&) const;
	bool operator!=(const bigInt&) const;
	bool operator<(const bigInt&) const;
	bool operator>(const bigInt&) const;
	bool operator<=(const bigInt&) const;
	bool operator>=(const bigInt&) const;

	operator std::string() const;
	operator int() const;

	size_t size() const;

	bool getSign() const;

	friend std::vector<long>* testing_vector_ptr(bigInt&);
private:
	std::vector<long> num; //the num stored in cells by 10^9, little-endian
	bool sign; //true - minus, false - plus

	const long& operator[](size_t) const;
	static const bigInt& absBigger(const bigInt&, const bigInt&);
	size_t getLength() const;
	const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<long>>> cbegin() const;
	const std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<long>>> cend() const;
	const std::reverse_iterator<std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<long>>>> crbegin() const;
	const std::reverse_iterator<std::_Vector_const_iterator<std::_Vector_val<std::_Simple_types<long>>>> crend() const;
};

bigInt operator+(const bigInt&, const bigInt&);
bigInt operator-(const bigInt&, const bigInt&);
bigInt operator/(const bigInt&, const bigInt&);
bigInt operator*(const bigInt&, const bigInt&);
bigInt operator%(const bigInt&, const bigInt&);
bigInt operator&(const bigInt&, const bigInt&);
bigInt operator|(const bigInt&, const bigInt&);
bigInt operator^(const bigInt&, const bigInt&);

std::ostream& operator<<(std::ostream&, const bigInt&);
std::istream& operator>>(std::istream&, bigInt&);
