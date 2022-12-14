#pragma once
#include <tuple>
#include <fstream>

template<typename... TupleTypes>
class CSVparser {
public:
	CSVparser(std::ifstream& f, const int skip = 0) : input_stream(f) { for(int i = 0; i < skip; i++) ignore(); }
private:
	std::tuple<TupleTypes...> string_tuple;
	std::ifstream input_stream;
};
