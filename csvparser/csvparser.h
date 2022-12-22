#pragma once
#include <tuple>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include "expts.h"

template <typename... TupleTypes>
class CsvParser {
private:
	char cell_delim;
	char line_delim;
	char screen_sym;
	std::size_t offset;
	std::ifstream& input_stream;
	std::tuple<TupleTypes...>* line_tuple;
	std::string line_str;
	
	class CsvIterator : public std::input_iterator_tag {
	public:
		CsvIterator(const bool s, CsvParser& c) : state(s), container(c) {}
		CsvIterator(const bool s, std::size_t offset, CsvParser& c) : state(s), container(c) {
			for (int i = 0; i < offset; i++) {
				getline(container.input_stream, container.line_str);
				if (container.input_stream.eof()) {
					throw offset_error();
				}
			}
		}
		CsvIterator(const CsvIterator& other) : state(other.state), container(other.container) {}

		CsvIterator& operator=(const CsvIterator& other) {
			if (this != &other) {
				state = other.state;
				line_tuple = other->line_tuple;
			}
		}

		CsvIterator& operator++() {
			state = container.read_next_line();
			return *this;
		}

		CsvIterator operator++(int) {
			CsvIterator temp(*this);
			++(*this);
			return temp;
		}

		bool operator==(const CsvIterator& other) {
			if (state != other.state)
				return false;
			//if (*line_tuple != other->line_tuple)
			//	return false;
			return true;
		}

		bool operator!=(const CsvIterator& other) {
			return !(*this == other);
		}

		std::tuple<TupleTypes...> operator*() {
			return *(container.line_tuple);
		}
		~CsvIterator() {}
	private:
		bool state; // state = 1 : there's something to read. 
				    // state = 0 : the end of file has been reached
		CsvParser& container;
	};
	
	bool read_next_line() {
		std::getline(input_stream, line_str);
		if (input_stream.eof())
			return 0;
		std::tuple<TupleTypes...>* new_line_tuple = new std::tuple<TupleTypes...>;
		*new_line_tuple = { 2, 2 };
		line_tuple = new_line_tuple;
		return 1;
	}/*
	void parse_line() {
		line_tuple<int, int> = { 1, 2 };
	}*/
	
	friend CsvIterator;
public:
	
	explicit CsvParser(std::ifstream& f, std::size_t o = 0, char cd = ',', char ld = '\n', char ss = '"') :
		input_stream(f), offset(o), line_tuple(nullptr), cell_delim(cd), line_delim(ld), screen_sym(ss) {}
	CsvIterator begin() { 
		CsvIterator it = CsvIterator(true, offset, *this);
		read_next_line(); 
		return it; 
	}
	CsvIterator end() { return CsvIterator(false, *this); }
};


