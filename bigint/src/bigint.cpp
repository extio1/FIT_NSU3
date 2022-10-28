#include "bigint.h"
#include <iostream>
#include <exception>
#include <stdlib.h>
using namespace std;
 

/// <summary>
/// 
/// Перенос копирования в список инициализации (конструктор копированием).
/// 
/// Внесение функций используемых только в данном cpp файле в анонимное пространсво имен.
/// 
/// operator[] теперь приватный.
/// 
/// Переработана реализация конструкторов от int и long long.
/// 
/// Присваивание копированием переписано явно.
/// 
/// Функции связанные с внутренним устройсвом bigNum были перенесены в private.
/// 
/// Убраны все предупреждения связанные с bigint.cpp
/// 
/// Добавлено присваивание перемещением. Почему оно nothrow?
/// 
/// </summary>
const int base = 1000000000;

vector<long>* testing_vector_ptr(bigInt& obj) {
	return &(obj.num);
}


const bigInt& bigInt::absBigger(const bigInt& i1, const bigInt& i2) {
	if (i1.getLength() > i2.getLength())
		return i1;
	else if (i1.getLength() < i2.getLength())
		return i2;
	else
		for (int i = i1.getLength() - 1; i >= 0; i--)
			if (i1[i] > i2[i])
				return i1;
	return i2;
}
void fill_num(long long inNum, bigInt& bint) {
	unsigned long long tempinNum = abs(inNum);
	while (tempinNum > 0) {
		bint.num.push_back(tempinNum % base);
		tempinNum /= base;
	}
}
namespace {
	void deleteLeadingZeros(vector<long>& num) {
		int toDelete = 0;
		for (int i = num.size() - 1; i >= 0; i--)
			if (num[i] == 0)
				toDelete++;
			else
				break;

		num.resize(num.size() - toDelete);
		num.shrink_to_fit();
	}
	inline bigInt abs(const bigInt& bint) {
		return ((bint.getSign()) ? -bint : bint);
	}
	long long findDivisor(const bigInt& i1, const bigInt& i2) {
		long long quotient = 0;
		long long left = 0;
		long long right = 1000000000000000;
		while (left < right) {
			long long middle = (left + right) / 2;
			if (abs(i2) * static_cast<bigInt>(middle) <= i1) {
				quotient = (static_cast<bigInt>(middle + 1) * abs(i2) <= i1) ? middle + 1 : middle;
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}
		return quotient;
	}
	string next_devident(string& ost, string& num, string& nextdiv, const bigInt& devisor, size_t* red, int& zeros) {
		string sub = "";
		zeros = -1;
		while (bigInt(nextdiv) < abs(devisor) && *red < num.size()) {
			sub = num.substr(*red, 1);
			nextdiv.append(sub);
			(*red) += sub.size();
			zeros++;
		}

		return nextdiv;
	}
	vector<bool> bigIntToBinarry(const bigInt& bint) {
		vector<bool> bin;
		bigInt temp(bint);
		while (temp > bigInt(0)) {
			bin.push_back(temp % bigInt(2));
			temp /= 2;
		}
		return bin;
	}
	bigInt binarryToBigInt(vector<bool>& bin) {
		bigInt bint;
		bigInt degree(1);
		for (bool digit : bin) {
			if (digit)
				bint += degree;
			degree *= 2;
		}
		return bint;
	}
}

size_t bigInt::getLength() const { return num.size(); }
bool bigInt::getSign() const { return sign; }
const _Vector_const_iterator<_Vector_val<_Simple_types<long>>> bigInt::cbegin() const { return num.cbegin(); }
const _Vector_const_iterator<_Vector_val<_Simple_types<long>>> bigInt::cend() const { return num.cend(); }
const reverse_iterator<_Vector_const_iterator<_Vector_val<_Simple_types<long>>>> bigInt::crbegin() const { return num.crbegin(); }
const reverse_iterator<_Vector_const_iterator<_Vector_val<_Simple_types<long>>>> bigInt::crend() const { return num.crend(); }

const long& bigInt::operator[](size_t pos) const {
	if (0 <= pos && pos < num.size())
		return num[pos];
	else
		throw out_of_range("");
}

bigInt::bigInt() : sign(false), num() {}
bigInt::bigInt(long long inNum) {
	sign = (inNum < 0);
	fill_num(inNum, *this);
}
bigInt::bigInt(int inNum) {
	sign = (inNum < 0);
	fill_num(inNum, *this);
}
bigInt::bigInt(string inNum) {
	if (inNum.size() != 0) {
		if (inNum.find_first_not_of("0123456789", 1) != string::npos && inNum[0] == '-' || \
			inNum.find_first_not_of("0123456789") != string::npos && inNum[0] != '-')
			throw invalid_argument("Nan");

		sign = (*(inNum.begin()) == '-');
		if (sign) { inNum.erase(0, 1); } //delete minus

		int lenBigNum = (inNum.size() - 1) / 9 + 1;
		num.resize(lenBigNum);

		int pos = 0;
		for (int i = inNum.size(); i > 0; i -= 9)
			if (i >= 9)
				num[pos++] = atol(inNum.substr(i - 9, 9).c_str());
			else
				num[pos++] = atol(inNum.substr(0, i).c_str());
	}
	else {
		sign = false;
		num.resize(0);
	}
	deleteLeadingZeros(num);
}
bigInt::bigInt(const bigInt& other) : sign(other.sign), num(other.num) {
}
bigInt::bigInt(bigInt&& other) noexcept : sign(move(other.sign)), num(move(other.num)) {
}
bigInt::~bigInt() {}

bigInt& bigInt::operator=(const bigInt& other) {
	cout << "Copy";
	if (this != &other) {
		bigInt temp = other;
		sign = temp.sign;
		num = temp.num;
	}
	return *this;
}
bigInt& bigInt::operator=(bigInt&& other) noexcept  {
	//cout << "Move" << '\n';
	//cout << &num << ' ' << &(other.num) << endl;
	if (this != &other) {
		sign = move(other.sign);
		num = move(num);
	}
	return *this;
}

bigInt bigInt::operator+() const {  // unary +
	bigInt temp(*this);
	return temp;
}
bigInt bigInt::operator-() const {	// unary -
	bigInt temp(*this);
	temp.sign = sign ^ true;
	return temp;
}

ostream& operator<<(ostream& outstr, const bigInt& bnum) {
	string out = string(bnum);
	outstr << out;
	return outstr;
}
istream& operator>>(istream& instr, bigInt& bnum) {
	string inNum;
	instr >> inNum;
	bnum = bigInt(inNum); //move assignment is called. bigInt(inNum) is temporary object &&
	return instr;
}

bigInt& bigInt::operator++() {
	*this = *this + bigInt(1);
	return *this;
}
bigInt& bigInt::operator--() {
	*this = *this - bigInt(1);
	return *this;
}
const bigInt bigInt::operator++(int) {
	bigInt temp;
	temp = *this;
	++(*this);
	return temp;
}
const bigInt bigInt::operator--(int) {
	bigInt temp;
	temp = *this;
	--(*this);
	return temp;
}

bigInt& bigInt::operator+=(const bigInt& i2) {
	int position = 0;
	bool carry = false;
	if (sign == i2.getSign()) {
		const bigInt& shorter = (num.size() <= i2.getLength()) ? *this : i2;
		const bigInt& longer = (shorter == *this) ? i2 : *this;

		for (size_t i = 0; i < longer.getLength(); i++) {
			long sum = ((i < shorter.getLength()) ? shorter[i] : 0) + longer[i] + carry;
			carry = sum >= base;
			if (i < num.size())
				num[i] = (sum % base);
			else
				num.push_back(sum % base);
		}
		if (carry)
			num.push_back(carry);
	}
	else {
		const bigInt& bigger = absBigger(*this, i2);
		const bigInt& lower = (bigger == *this) ? i2 : *this;
		size_t length_bigger = bigger.getLength();
		size_t length_lower = lower.getLength();
		sign = bigger.getSign();
		long sum = 0;
		int pos = 0;
		for (size_t i = 0; i < length_bigger; i++) {
			if (i < length_lower) {
				if (bigger[i] - carry < lower[i]) {
					sum = bigger[i] - carry - lower[i] + base;
					carry = true;
				}
				else {
					sum = bigger[i] - carry - lower[i];
					carry = false;
				}
			}
			else {
				sum = bigger[i] - carry + base;
				if (bigger[i] - carry > 0)
					carry = false;
			}
			if (i < num.size())
				num[i] = (sum % base);
			else
				num.push_back(sum % base);
			pos++;
		}
		for (size_t i = pos; i < length_bigger && carry; i++) {
			if (bigger[i] != 0) {
				num[i] = bigger[i] - 1;
				carry = false;
			}
		}
		deleteLeadingZeros(num);
	}
	return *this;
}
bigInt& bigInt::operator-=(const bigInt& i2) {
	bigInt temp = i2;
	temp = -temp;
	*this += temp;
	return *this;
}
bigInt& bigInt::operator/=(const bigInt& i2) {
	if (i2.getLength() == 0)
		throw "Division by zero";
	if (*this < i2) {
		*this = 0;
		return *this;
	}
	int zeros = -1;
	size_t red = 0;
	sign = (sign ^ i2.getSign());
	string i2numstr = static_cast<string>(*this);
	string i1numstr = "";
	i1numstr = next_devident(i1numstr, i2numstr, i1numstr, i2, &red, zeros);
	string answer = "";
	zeros = -1;

	while (red <= i2numstr.size()) {
		for (int i = 0; i < zeros; i++)
			answer.append("0");

		bigInt i1 = i1numstr;
		long long quotient = findDivisor(i1, i2);
		answer.append(to_string(quotient));

		i1 = abs(i1);
		i1 -= (static_cast<bigInt>(quotient) * i2);
		i1numstr = static_cast<string>(i1);

		if (red == i2numstr.size())
			break;

		if (red < i2numstr.size())
			i1numstr = next_devident(i1numstr, i2numstr, i1numstr, i2, &red, zeros);
	}
	*this = answer;
	return *this;
}
bigInt& bigInt::operator*=(const bigInt& i2) {
	vector<long> temp;
	temp.reserve(num.size() + i2.getLength());
	temp.resize(num.size() + i2.getLength());
	sign ^= i2.getSign();
	unsigned long long carry = 0;
	int lastPosition = 0;
	for (size_t i = 0; i < num.size(); i++) {
		carry = 0;
		for (size_t j = 0; j < i2.getLength() || carry; j++) {
			unsigned long long cur = 1ll * num[i] * ((j < i2.getLength()) ? i2[j] : 0) + carry + temp[i + j];
			temp[i + j] = cur % base;
			carry = cur / base;
		}
	}

	deleteLeadingZeros(temp);
	num = temp;
	return *this;
}
bigInt& bigInt::operator%=(const bigInt& i2) {
	if (*this < i2)
		return *this;
	if (*this == i2) {
		*this = 0;
		return *this;
	}

	bigInt temp = *this / i2;
	temp = *this - (i2 * temp);
	*this = temp;
	return *this;
}

bigInt operator+(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp += i2;
	return temp;
}
bigInt operator-(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp -= i2;
	return temp;
}
bigInt operator*(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp *= i2;
	return temp;
}
bigInt operator/(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp /= i2;
	return temp;
}
bigInt operator%(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp %= i2;
	return temp;
}

bool bigInt::operator==(const bigInt& a1) const {
	if (num.size() != a1.num.size() || sign != a1.sign)
		return false;
	int i = 0;
	for (long part : a1.num)
		if (part != num[i++])
			return false;
	return true;
}
bool bigInt::operator!=(const bigInt& a1) const {
	return !(*this == a1);
}
bool bigInt::operator<(const bigInt& a1) const {
	if (sign == true && a1.sign == false || num.size() < a1.num.size())
		return true;
	if (sign == false && a1.sign == true || num.size() > a1.num.size())
		return false;
	for (int i = num.size() - 1; i >= 0; i--)
		if (num[i] != a1.num[i])
			if (num[i] < a1.num[i] && sign == false || num[i] > a1.num[i] && sign == true)
				return true;
			else
				return false;
	return false;
}
bool bigInt::operator>(const bigInt& a1) const {
	return !(*this < a1) && *this != a1;
}
bool bigInt::operator<=(const bigInt& a1) const {
	return (*this < a1) || (*this == a1);
}
bool bigInt::operator>=(const bigInt& a1) const {
	return *this > a1 || *this == a1;
}

bigInt bigInt::operator~() const {
	vector<bool> bin = bigIntToBinarry(*this);
	for (size_t i = 0; i < bin.size(); i++)
		cout << bin[i];
	cout << endl;
	if (bin.size() == 0) {
		bin.push_back(false);
		bin.push_back(true);
	}
	for (size_t i = 0; i < bin.size(); i++)
		bin[i] = !bin[i];
	bigInt bintadd = ++binarryToBigInt(bin);
	bintadd.sign = !(this->sign);
	return bintadd;
}
bigInt& bigInt::operator^=(const bigInt& i2) {
	vector<bool> xorbin;
	bigInt temp1 = *this;
	bigInt temp2 = i2;
	while (temp1 > bigInt(0) || temp2 > bigInt(0))
		if (temp1 > bigInt(0) && temp2 > bigInt(0)) {
			xorbin.push_back(int(temp1 % bigInt(2)) ^ int(temp2 % bigInt(2)));
			temp1 /= 2;
			temp2 /= 2;
		}
		else if (temp1 > bigInt(0)) {
			xorbin.push_back(int(temp1 % bigInt(2)));
			temp1 /= 2;
		}
		else {
			xorbin.push_back(int(temp2 % bigInt(2)));
			temp2 /= 2;
		}

	*this = binarryToBigInt(xorbin);
	return *this;
}
bigInt& bigInt::operator&=(const bigInt& i2) {
	vector<bool> andbin;
	bigInt temp1 = *this;
	bigInt temp2 = i2;
	while (temp1 > bigInt(0) && temp2 > bigInt(0))
		if (temp1 > bigInt(0) && temp2 > bigInt(0)) {
			andbin.push_back(int(temp1 % bigInt(2)) & int(temp2 % bigInt(2)));
			temp1 /= 2;
			temp2 /= 2;
		}

	*this = binarryToBigInt(andbin);
	return *this;
}
bigInt& bigInt::operator|=(const bigInt& i2) {
	vector<bool> orbin;
	vector<bool> test = bigIntToBinarry(i2);

	bigInt temp1 = *this;
	bigInt temp2 = i2;
	while (temp1 > bigInt(0) || temp2 > bigInt(0))
		if (temp1 > bigInt(0) && temp2 > bigInt(0)) {
			orbin.push_back(int(temp1 % bigInt(2)) | int(temp2 % bigInt(2)));
			temp1 /= 2;
			temp2 /= 2;
		}
		else if (temp1 > bigInt(0)) {
			orbin.push_back(int(temp1 % bigInt(2)));
			temp1 /= 2;
		}
		else {
			orbin.push_back(int(temp2 % bigInt(2)));
			temp2 /= 2;
		}

	*this = binarryToBigInt(orbin);
	return *this;
}
bigInt operator&(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp &= i2;
	return temp;
}
bigInt operator|(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp |= i2;
	return temp;
}
bigInt operator^(const bigInt& i1, const bigInt& i2) {
	bigInt temp = i1;
	temp ^= i2;
	return temp;
}

bigInt::operator string() const {
	string out;
	if (num.size() == 0) {
		out.append("0");
		return out;
	}
	if (sign)
		out.append("-");

	for (auto i = num.crbegin(); i != num.crend(); i++)
		if (*i == 0 && num.size() != 1)
			out.append("000000000");
		else {
			int lenNum = to_string(*i).length();
			if (lenNum != 9 && i != num.crbegin()) {
				for (int j = 0; j < 9 - lenNum; j++)
					out.append("0", 1);
				out.append(to_string(*i));
			}
			else {
				out.append(to_string(*i));
			}
		}

	return out;
}
bigInt::operator int() const {
	int out = 0;
	bigInt absBint = *this;
	absBint.sign = false;
	bigInt temp = (absBint != bigInt(INT_MAX)) ? absBint % bigInt(INT_MAX) : bigInt(INT_MAX);
	if (temp.num.size() == 1) {
		out = temp.num[0];
	}
	else if (temp.num.size() == 2) {
		out = temp.num[0] + temp.num[1] * base;
	}
	out = (sign) ? -out : out;
	return out;
}

size_t bigInt::size() const {
	return (num.size() * 4 + sizeof(sign));
}
