#include "pch.h"
#include "../oop_prakt/bigint.cpp"
#include "C:\Users\User\source\repos\prakt1\ap-master\ap.hpp"
using namespace std;
/// 
/// В ин(де)кременты были добавлены проверки возвращаемого значения.
/// 
/// Теперь во всех арифметических операциях проверяется коммутативность. Явное указание
/// размера передаемого массива в CorrectCalc заменено на size() от него.
/// 
/// Конструктор копирования проверяет, что полученный объект не меняет оригинал.
/// Конструктор перемещение проверяет, что полученный объект меняет оригинал.
/// 
/// Присваивание копированием проверяет, что копия не меняет оригинал.
/// 
/// В бинарный или добавлен тест, где операнды большое и маленькое число. Аналогичные изменения
/// в тестах для &, ^.
/// 
/// Добавлен тест с вычислением произвольного выражения.
/// 
/// Добавлен тест на присваивание перемещением.
/// 
TEST(Constructor, Empty) {
	ASSERT_NO_THROW(bigInt a);
	bigInt a;
	ASSERT_EQ(0, int(a));
}
TEST(Constructor, Integer) {
	ASSERT_NO_THROW(bigInt a(0));
	bigInt a1(0);
	bigInt a2(-1);
	bigInt a3(1);
	bigInt a4(INT_MAX);
	bigInt a5(INT_MIN);
	bigInt a6(1'000'000'000);
	bigInt a7(-1000000000);
	bigInt a8(1'428'762'438);
	ASSERT_EQ(0, static_cast<int>(a1));
	ASSERT_EQ(-1, static_cast<int>(a2));
	ASSERT_EQ(1, static_cast<int>(a3));
	ASSERT_EQ(INT_MAX, static_cast<int>(a4));
	ASSERT_EQ("-2147483648", static_cast<string>(a5));
	ASSERT_EQ(1000000000, static_cast<int>(a6));
	ASSERT_EQ(-1000000000, static_cast<int>(a7));
	ASSERT_EQ(1428762438, static_cast<int>(a8));
}
TEST(Constructor, LongLong) {
	ASSERT_NO_THROW(bigInt a(0));
	bigInt a1(0);
	bigInt a2(-1);
	bigInt a3(1);
	bigInt a4(LLONG_MAX);
	bigInt a5(LLONG_MIN);
	bigInt a6(9000000000000000000);
	bigInt a7(-9000000000000000000);
	bigInt a8(1111111111111111111);
	ASSERT_EQ("0", static_cast<string>(a1));
	ASSERT_EQ("-1", static_cast<string>(a2));
	ASSERT_EQ("1", static_cast<string>(a3));
	ASSERT_EQ("9223372036854775807", static_cast<string>(a4));
	ASSERT_EQ("-9223372036854775808", static_cast<string>(a5));
	ASSERT_EQ("9000000000000000000", static_cast<string>(a6));
	ASSERT_EQ("-9000000000000000000", static_cast<string>(a7));
	ASSERT_EQ("1111111111111111111", static_cast<string>(a8));
}
TEST(Constructor, String) {
	ASSERT_NO_THROW(bigInt a(""));
	ASSERT_THROW(bigInt a("-12332e243534"), invalid_argument);
	ASSERT_THROW(bigInt a("9223423433333333333f33333565477777768"), invalid_argument);
	ASSERT_THROW(bigInt a("thereisnonumber"), invalid_argument);

	bigInt a1("1");
	bigInt a2("0");
	bigInt a3("-1");
	bigInt a4("9999999888888888888888888888777777777777777777776666666666666666666666666655555555555555553333333333");
	bigInt a5("0000000000000001");
	bigInt a6("-0000000000400000002");
	bigInt a7("123456789");

	ASSERT_EQ("1", static_cast<string>(a1));
	ASSERT_EQ("0", static_cast<string>(a2));
	ASSERT_EQ("-1", static_cast<string>(a3));
	ASSERT_EQ("9999999888888888888888888888777777777777777777776666666666666666666666666655555555555555553333333333", static_cast<string>(a4));
	ASSERT_EQ("1", static_cast<string>(a5));
	ASSERT_EQ(bigInt(-400000002), a6);
	ASSERT_EQ(bigInt(123456789), a7);
}
TEST(Constructor, Copy) {
	bigInt a("-123456789101112");
	bigInt b(a);
	ASSERT_EQ(a, b);
	b += 123456789101112;
	ASSERT_EQ(0, int(b));
	ASSERT_EQ("-123456789101112", string(a));
	b += 1ll * INT_MAX + 100000;
	b = int(b);
	ASSERT_EQ("100000", string(b));
	ASSERT_EQ("-123456789101112", string(a));
}
TEST(Constructor, Move) {
	string num1 = "123";
	string num2 = "456";
	string&& num3 = num1 + num2;
	bigInt a1(num3);

	bigInt a2("123456");
	ASSERT_EQ(a1, a2);

	bigInt c(move(a2));
	ASSERT_EQ("123456", string(c));
	ASSERT_NE("123456", string(a2));
}

TEST(Assignment, Copy) {
	bigInt a("9999999999");
	bigInt b(a);
	ASSERT_NO_THROW(a = a);
	ASSERT_EQ(b, a);

	b = bigInt(315);
	a = b;
	ASSERT_EQ(b, a);

	b -= 315;
	ASSERT_EQ(0, int(b));
	ASSERT_NE(a, b);
	ASSERT_EQ("315", string(a));
}
TEST(Assignment, Move) {
	bigInt a;
	string astring = "999999999999";
	a = move(astring);
	ASSERT_EQ("999999999999", string(a));
	ASSERT_NE("999999999999", astring);

	bigInt b("11111111111111");
	bigInt bmoved;
	bmoved = move(b);
	ASSERT_EQ("11111111111111", string(bmoved));
	ASSERT_NE("11111111111111", string(b));
	bigInt b_before_op(b);
	bmoved *= 9;
	ASSERT_EQ("99999999999999", string(bmoved));
	ASSERT_EQ(b_before_op, b);
}

TEST(Cast, BigInt_String) {
	bigInt a0("111111111");
	ASSERT_EQ("111111111", static_cast<string>(a0));
	bigInt a1("1000000000");
	ASSERT_EQ("1000000000", static_cast<string>(a1));
	bigInt a2("");
	ASSERT_EQ("0", static_cast<string>(a2));
	bigInt a3("0");
	ASSERT_EQ("0", static_cast<string>(a3));
}
TEST(Cast, BigInt_Int) {
	bigInt a0("111111111");
	ASSERT_EQ(111111111, static_cast<int>(a0));
	bigInt a1("1000000000");
	ASSERT_EQ(1000000000, static_cast<int>(a1));
	bigInt a2;
	ASSERT_EQ(0, static_cast<int>(a2));
	bigInt a3(0);
	ASSERT_EQ(0, static_cast<int>(a3));
	bigInt a4("100000000000000000000000000");
	ASSERT_EQ(517667057, static_cast<int>(a4)); // 517667057 = 100000000000000000000000000 % INT_MAX 
	bigInt a5("-2650497834082571398");
	ASSERT_EQ(0, static_cast<int>(a5)); // 0 = 2650497834082571398 % INT_MAX
	bigInt a6("-22342232432342234398");
	ASSERT_EQ(-1326944558, static_cast<int>(a6)); // 1326944558 = 22342232432342234398 % INT_MAX 
}

TEST(Increments, Pre) {
	bigInt a1 = 123123;
	bigInt a11 = ++a1;
	ASSERT_EQ("123124", string(a1));
	ASSERT_EQ("123124", string(a11));
	bigInt a2 = -1;
	bigInt a21 = ++a2;
	ASSERT_EQ("0", string(a2));
	ASSERT_EQ("0", string(a21));
	bigInt a3 = 999999999999999999;
	bigInt a31 = ++a3;
	ASSERT_EQ("1000000000000000000", string(a3));
	ASSERT_EQ("1000000000000000000", string(a31));
	bigInt a4 = -1000000000000000000;
	bigInt a41 = ++a4;
	ASSERT_EQ("-999999999999999999", string(a4));
	ASSERT_EQ("-999999999999999999", string(a41));
	bigInt a5 = "18923719823791827398127398127391827389173918237192837";
	bigInt a51 = ++a5;
	ASSERT_EQ("18923719823791827398127398127391827389173918237192838", string(a5));
	ASSERT_EQ("18923719823791827398127398127391827389173918237192838", string(a51));
}

TEST(Increments, Post) {
	bigInt a1 = 123123;
	bigInt a11 = a1++;
	ASSERT_EQ("123124", string(a1));
	ASSERT_EQ("123123", string(a11));

	bigInt a2 = -1;
	bigInt a21 = a2++;
	ASSERT_EQ("0", string(a2));
	ASSERT_EQ("-1", string(a21));

	bigInt a3 = 999999999999999999;
	bigInt a31 = a3++;
	ASSERT_EQ("1000000000000000000", string(a3));
	ASSERT_EQ("999999999999999999", string(a31));

	bigInt a4 = -1000000000000000000;
	bigInt a41 = a4++;
	ASSERT_EQ("-999999999999999999", string(a4));
	ASSERT_EQ("-1000000000000000000", string(a41));

	bigInt a5 = "18923719823791827398127398127391827389173918237192837";
	bigInt a51 = a5++;
	ASSERT_EQ("18923719823791827398127398127391827389173918237192838", string(a5));
	ASSERT_EQ("18923719823791827398127398127391827389173918237192837", string(a51));
}
TEST(Decrements, Post) {
	bigInt a1 = 123123;
	bigInt a11 = a1--;
	ASSERT_EQ("123122", string(a1));
	ASSERT_EQ("123123", string(a11));

	bigInt a2 = 0;
	bigInt a21 = a2--;
	ASSERT_EQ("-1", string(a2));
	ASSERT_EQ("0", string(a21));

	bigInt a3 = 1000000000000000000;
	bigInt a31 = a3--;
	ASSERT_EQ("999999999999999999", string(a3));
	ASSERT_EQ("1000000000000000000", string(a31));

	bigInt a4 = -999999999999999999;
	bigInt a41 = a4--;
	ASSERT_EQ("-1000000000000000000", string(a4));
	ASSERT_EQ("-999999999999999999", string(a41));

	bigInt a5 = "18923719823791827398127398127391827389173918237192837";
	bigInt a51 = a5--;
	ASSERT_EQ("18923719823791827398127398127391827389173918237192836", string(a5));
	ASSERT_EQ("18923719823791827398127398127391827389173918237192837", string(a51));
}
TEST(Decrements, Pre) {
	bigInt a1 = 123123;
	bigInt a11 = --a1;
	ASSERT_EQ("123122", string(a1));
	ASSERT_EQ("123122", string(a11));

	bigInt a2 = 0;
	bigInt a21 = --a2;
	ASSERT_EQ("-1", string(a2));
	ASSERT_EQ("-1", string(a21));

	bigInt a3 = 1000000000000000000;
	bigInt a31 = --a3;
	ASSERT_EQ("999999999999999999", string(a3));
	ASSERT_EQ("999999999999999999", string(a31));

	bigInt a4 = -999999999999999999;
	bigInt a41 = --a4;
	ASSERT_EQ("-1000000000000000000", string(a4));
	ASSERT_EQ("-1000000000000000000", string(a41));

	bigInt a5 = "18923719823791827398127398127391827389173918237192837";
	bigInt a51 = --a5;
	ASSERT_EQ("18923719823791827398127398127391827389173918237192836", string(a5));
	ASSERT_EQ("18923719823791827398127398127391827389173918237192836", string(a51));
}

TEST(UnarySign, Plus) {
	bigInt a1 = 0;
	bigInt a2 = -123;
	bigInt a3 = 123;
	bigInt a4 = "10000000000000000000000000000000000000";
	bigInt a5 = "-10000000000000000000000000000000000000";
	ASSERT_EQ(0, int(+a1));
	ASSERT_EQ(-123, int(+a2));
	ASSERT_EQ(123, int(+a3));
	ASSERT_EQ("10000000000000000000000000000000000000", string(+a4));
	ASSERT_EQ("-10000000000000000000000000000000000000", string(+a5));
}
TEST(UnarySign, Minus) {
	bigInt a1 = 0;
	bigInt a2 = -123;
	bigInt a3 = 123;
	bigInt a4 = "10000000000000000000000000000000000000";
	bigInt a5 = "-10000000000000000000000000000000000000";
	ASSERT_EQ(0, int(-a1));
	ASSERT_EQ(123, int(-a2));
	ASSERT_EQ(-123, int(-a3));
	ASSERT_EQ("-10000000000000000000000000000000000000", string(-a4));
	ASSERT_EQ("10000000000000000000000000000000000000", string(-a5));
}
TEST(OrderOpers, Equal) {
	ASSERT_EQ(bigInt("123") == bigInt("123"), true);
	ASSERT_EQ(bigInt("-123") == bigInt("123"), false);
	ASSERT_EQ(bigInt("0") == bigInt(), true);
	ASSERT_EQ(bigInt("") == bigInt("0"), true);
	ASSERT_EQ(bigInt("") == bigInt(""), true);
	ASSERT_EQ(bigInt("1") == bigInt("123"), false);
	ASSERT_EQ(bigInt("123123") == bigInt("123"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000001") == bigInt("1000000000000000000000000000"), false);
}
TEST(OrderOpers, NotEqual) {
	ASSERT_EQ(bigInt("123") != bigInt("123"), false);
	ASSERT_EQ(bigInt("-123") != bigInt("123"), true);
	ASSERT_EQ(bigInt("0") != bigInt(), false);
	ASSERT_EQ(bigInt("") != bigInt("0"), false);
	ASSERT_EQ(bigInt("") != bigInt(""), false);
	ASSERT_EQ(bigInt("1") != bigInt("123"), true);
	ASSERT_EQ(bigInt("123123") != bigInt("123"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000001") != bigInt("1000000000000000000000000000"), true);
}
TEST(OrderOpers, Less) {
	ASSERT_EQ(bigInt("123") < bigInt("123"), false);
	ASSERT_EQ(bigInt("-123") < bigInt("123"), true);
	ASSERT_EQ(bigInt("0") < bigInt(), false);
	ASSERT_EQ(bigInt("") < bigInt("0"), false);
	ASSERT_EQ(bigInt("") < bigInt(""), false);
	ASSERT_EQ(bigInt("1") < bigInt("123"), true);
	ASSERT_EQ(bigInt("123123") < bigInt("123"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000000") < bigInt("9000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000000") < bigInt("-10000000000000000000000000000000000"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000000") < bigInt("1000000000000000000000000001"), true);
	ASSERT_EQ(bigInt("-123123") < bigInt("123"), true);
}
TEST(OrderOpers, More) {
	ASSERT_EQ(bigInt("123") > bigInt("123"), false);
	ASSERT_EQ(bigInt("-123") > bigInt("123"), false);
	ASSERT_EQ(bigInt("0") > bigInt(), false);
	ASSERT_EQ(bigInt("") > bigInt("0"), false);
	ASSERT_EQ(bigInt("") > bigInt(""), false);
	ASSERT_EQ(bigInt("1") > bigInt("123"), false);
	ASSERT_EQ(bigInt("123123") > bigInt("123"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000000") > bigInt("9000000000000000000000000000"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000000") > bigInt("-10000000000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000001") > bigInt("1000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("-123123") > bigInt("123"), false);
}
TEST(OrderOpers, MoreOrEqual) {
	ASSERT_EQ(bigInt("1") >= bigInt("1"), true);
	ASSERT_EQ(bigInt("-123") >= bigInt("123"), false);
	ASSERT_EQ(bigInt("0") >= bigInt(), true);
	ASSERT_EQ(bigInt("") >= bigInt("0"), true);
	ASSERT_EQ(bigInt("") >= bigInt(""), true);
	ASSERT_EQ(bigInt("1") >= bigInt("123"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000000") >= bigInt("1000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000000") >= bigInt("-1000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000000") >= bigInt("-10000000000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000001") >= bigInt("1000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("-123123") >= bigInt("123"), false);
}
TEST(OrderOpers, LessOrEqual) {
	ASSERT_EQ(bigInt("1") <= bigInt("1"), true);
	ASSERT_EQ(bigInt("-123") <= bigInt("123"), true);
	ASSERT_EQ(bigInt("0") <= bigInt(), true);
	ASSERT_EQ(bigInt("") <= bigInt("0"), true);
	ASSERT_EQ(bigInt("") <= bigInt(""), true);
	ASSERT_EQ(bigInt("1") <= bigInt("12345678910"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000000") <= bigInt("1000000000000000000000000000"), true);
	ASSERT_EQ(bigInt("1000000000000000000000000000") <= bigInt("-1000000000000000000000000000"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000000") <= bigInt("-10000000000000000000000000000000000"), false);
	ASSERT_EQ(bigInt("1000000000000000000000000001") <= bigInt("1000000000000000000000000000"), false);
	ASSERT_EQ(bigInt("-123123") <= bigInt("123"), true);
}

TEST(Size, Size) {
	bigInt a1(12);
	ASSERT_EQ(5, a1.size());
	bigInt a2(123456789);
	ASSERT_EQ(5, a2.size());
	bigInt a3("123456789123456789123456789123456789");
	ASSERT_EQ(17, a3.size());
	bigInt a4(-123456789);
	ASSERT_EQ(5, a4.size());
	bigInt a5("-123456789123456789123456789123456789");
	ASSERT_EQ(17, a5.size());
	bigInt a6(0);
	ASSERT_EQ(1, a6.size());
}

::testing::AssertionResult CorrectCalc(bigInt* bintArgs, size_t nArgs, char oper) {
	ap_int<256>* testerArgs = new ap_int<256>[nArgs];
	for (size_t i = 0; i < nArgs; i++)
		testerArgs[i] = static_cast<string>(bintArgs[i]);

	if (oper == '+')
		for (size_t i = 0; i < nArgs; i++)
			for (size_t j = 0; j < nArgs; j++)
				if (static_cast<string>(bintArgs[i] + bintArgs[j]) != static_cast<string>(testerArgs[i] + testerArgs[j]))
					return ::testing::AssertionFailure() << bintArgs[i] << ' ' << oper << ' ' << bintArgs[j] << \
					" not equal " << testerArgs[i] + testerArgs[j];
	else if (oper == '-')
		for (size_t i = 0; i < nArgs; i++)
			for (size_t j = 0; j < nArgs; j++)
				if (static_cast<string>(bintArgs[i] - bintArgs[j]) != static_cast<string>(testerArgs[i] - testerArgs[j]))
					return ::testing::AssertionFailure() << bintArgs[i] << ' ' << oper << ' ' << bintArgs[j] << \
					" not equal " << testerArgs[i] - testerArgs[j];
	else if (oper == '*')
		for (size_t i = 0; i < nArgs; i++)
			for (size_t j = 0; j < nArgs; j++)
				if (static_cast<string>(bintArgs[i] * bintArgs[j]) != static_cast<string>(testerArgs[i] * testerArgs[j]))
					return ::testing::AssertionFailure() << bintArgs[i] << ' ' << oper << ' ' << bintArgs[j] << \
					" not equal " << testerArgs[i] * testerArgs[j];
	else if (oper == '/')
		for (size_t i = 0; i < nArgs; i++)
			for (size_t j = 0; j < nArgs; j++)
				if (static_cast<string>(bintArgs[i] / bintArgs[j]) != static_cast<string>(testerArgs[i] / testerArgs[j]))
					return ::testing::AssertionFailure() << bintArgs[i] << ' ' << oper << ' ' << bintArgs[j] << \
					" not equal " << testerArgs[i] / testerArgs[j];
	else if (oper == '%')
		for (size_t i = 0; i < nArgs; i++)
			for (size_t j = 0; j < nArgs; j++)
				if (static_cast<string>(bintArgs[i] % bintArgs[j]) != static_cast<string>(testerArgs[i] % testerArgs[j]))
					return ::testing::AssertionFailure() << bintArgs[i] << ' ' << oper << ' ' << bintArgs[j] << \
					" not equal " << testerArgs[i] % testerArgs[j];

	return ::testing::AssertionSuccess();
}
TEST(Arithmetic, Plus) {
	bigInt argsToTest[10] = { 1, 0, -1, 999999999, -999999999, "1000000000000000000000000000",\
							 "-1000000000000000000000000000", "3150389049001230192301923",\
							 "99999999999999999999999999999", "-12312312312312543645460000007" };
	EXPECT_TRUE(CorrectCalc(argsToTest, size(argsToTest), '+'));
}

//при создании вектора возникает проблема с конструкторами для указателся на char
TEST(Arithmetic, Minus) {
	bigInt argsToTest[10] = { 1, 0, -1, "999999999", "-999999999", "1000000000000000000000000000",\
							 "-1000000000000000000000000000", "3150389049001230192301923",\
							 "99999999999999999999999999999", "-12312312312312543645460000007" };
	EXPECT_TRUE(CorrectCalc(argsToTest, size(argsToTest), '-'));
}
TEST(Arithmetic, Multiply) {
	bigInt argsToTest[16] = { 1, 0, -1, 999999999, -999999999, "1000000000000000000000000000",\
							 "-1000000000000000000000000000", "3150389049001230192301923",\
							 "99999999999999999999999999999", "-12312312312312543645460000007",\
							 2, 3, 4, 5, 10, 1000000 };
	EXPECT_TRUE(CorrectCalc(argsToTest, 16, '*'));
}
TEST(Arithmetic, Division) {
	bigInt argsToTest[17] = { 1, 0, -1, 999999999, -999999999, "1000000000000000000000000000",\
							 "-1000000000000000000000000000", "3150389049001230192301923",\
							 "99999999999999999999999999999", "-12312312312312543645460000007",\
							 2, 3, 4, 5, 10, 1000000, "99999999999999999999999999999" };
	EXPECT_TRUE(CorrectCalc(argsToTest, size(argsToTest), '/'));
	ASSERT_ANY_THROW(bigInt(123456) / bigInt("0"));
	ASSERT_ANY_THROW(bigInt(123456) / (bigInt(1) - bigInt(1)));
}
TEST(Arithmetic, Mod) {
	bigInt argsToTest[16] = { 1, 0, -1, 999999999, -999999999, "1000000000000000000000000000",\
							 "-1000000000000000000000000000", "3150389049001230192301923",\
							 "99999999999999999999999999999", "-12312312312312543645460000007",\
							 2, 3, 4, 5, 10, 1000000 };
	EXPECT_TRUE(CorrectCalc(argsToTest, size(argsToTest), '%'));
}

TEST(Binary, Or) {
	bigInt a1(5); // 101
	bigInt a2(2); // 010
	ASSERT_EQ(bigInt(7), a1 | a2);
	bigInt b1(8796093022209); // 10000000000000000000000000000000000000000001
	bigInt b2(8796093022206); // 01111111111111111111111111111111111111111110
	ASSERT_EQ(bigInt(17592186044415), b1 | b2);
	bigInt c1("123456789123456789123456789");
	bigInt c2("123456789123456789123456789");
	ASSERT_EQ(bigInt("123456789123456789123456789"), c1 | c2);
	bigInt d1("123456789123456789123456789");
	bigInt d2(0);
	ASSERT_EQ("123456789123456789123456789", string(d1 | d2));
	bigInt e1("123456789123456789123456789123456789");
	bigInt e2(500);
	ASSERT_EQ("123456789123456789123456789123457013", string(e1 | e2));
}
TEST(Binary, And) {
	bigInt a1(5); // 101
	bigInt a2(2); // 010
	ASSERT_EQ(bigInt(0), a1 & a2);
	bigInt b1(8796093022209); // 10000000000000000000000000000000000000000001
	bigInt b2(8796093022206); // 01111111111111111111111111111111111111111110
	ASSERT_EQ(bigInt(0), b1 & b2);
	bigInt c1("123456789123456789123456789");
	bigInt c2("123456789123456789123456789");
	ASSERT_EQ(bigInt("123456789123456789123456789"), c1 & c2);
	bigInt d1("123456789123456789123456789");
	bigInt d2(0);
	ASSERT_EQ(bigInt(0), string(d1 & d2));
	bigInt e1("3022842232837"); // 101011111111001111011100000000000000000101
	bigInt e2("4389512151051"); // 111111111000000011010100000000000000001011
	ASSERT_EQ(bigInt("3015122616321"), e1 & e2);
	bigInt f1("123456789123456789123456789");
	bigInt f2(12345);
	ASSERT_EQ("4113", string(f1 & f2));
}
TEST(Binary, Xor) {
	bigInt a1(5); // 101
	bigInt a2(2); // 010
	ASSERT_EQ(bigInt(7), a1 ^ a2);
	bigInt b1(8796093022209); // 10000000000000000000000000000000000000000001
	bigInt b2(8796093022206); // 01111111111111111111111111111111111111111110
	ASSERT_EQ(bigInt(17592186044415), b1 ^ b2);
	bigInt c1("123456789123456789123456789");
	bigInt c2("123456789123456789123456789");
	ASSERT_EQ(bigInt(0), c1 ^ c2);
	bigInt d1("123456789123456789123456789"); //110011000011110111111011111001011100011101100011001111101111100000001000101111100010101
	bigInt d2(0);
	ASSERT_EQ(bigInt("123456789123456789123456789"), string(d1 ^ d2));
	bigInt e1("3022842232837"); // 101011111111001111011100000000000000000101
	bigInt e2("4389512151051"); // 111111111000000011010100000000000000001011
	ASSERT_EQ(bigInt("1382109151246"), e1 ^ e2);
	bigInt f1("123456789123456789123456789");
	bigInt f2(12345);
	ASSERT_EQ("123456789123456789123460908", string(f1 ^ f2));
}
TEST(Binary, Supl) {
	bigInt a(0);
	ASSERT_EQ("-2", string(~a));
	bigInt b(8796093022206);
	ASSERT_EQ("-2", string(~b));
	bigInt c(-2);
	ASSERT_EQ("2", string(~c));
	bigInt d("8796093022210");
	ASSERT_EQ("-8796093022206", string(~d));
}
TEST(Large, Bunch) {
	bigInt a;
	a = ((bigInt("128719827391827498123749817234981274") + bigInt(222222) * bigInt(983234))\
		- bigInt("999999999999999999999999999999999999999")) * bigInt(-1) / bigInt("9999999999999999999999");
	ASSERT_EQ("99987128017260817", string(a));
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
