#pragma once
#include <tuple>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <memory>
#include "excpts.h"
#include "tupleio.h"


template <typename... TupleTypes>
class CsvParser {
private:
	Format format;
	std::size_t offset;
	std::ifstream& input_stream;
	std::tuple<TupleTypes...>* line_tuple;
	std::size_t line_counter;
	
	class CsvIterator : public std::input_iterator_tag {
	public:
		CsvIterator(const bool s, CsvParser& c) : state(s), container(c) { }
		CsvIterator(const bool s, std::size_t offset, CsvParser& c) : state(s), container(c) {
			std::string line_str;
			for (int i = 0; i < offset; i++) {
				getline(container.input_stream, line_str);
				if (container.input_stream.eof()) {
					throw offset_error(offset);
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
			container.read_next_line();
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
			return true;
		}

		bool operator!=(const CsvIterator& other) {
			bool res = !(*this == other);
			if (container.input_stream.eof())
				state = 0;
			return res;
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
		++line_counter;
		if (input_stream.eof())
			return 0;
		try {
			auto new_tuple_ptr = read_tuple(input_stream, line_tuple, format);
			line_tuple = new_tuple_ptr;
		}
		catch (cell_error ce) {
			std::cerr << ce.what();
			std::cerr << "Error in data row " << line_counter << " col " << ce.get_col() << '\n';
		}

		return 1;
	}

	friend CsvIterator;
public:

	explicit CsvParser(std::ifstream& f, std::size_t o = 0, char cd = ',', char ld = '\n', char ss = '"') :
		input_stream(f), offset(o), format(cd, ld, ss), line_counter(0) {
		line_tuple = new std::tuple<TupleTypes...>;
	}

	CsvIterator begin() {
		CsvIterator it = CsvIterator(true, offset, *this);
		read_next_line();
		return it;
	}

	void configure(char cell = ',', char line = '\n', char screen = '"') {
		format.cell_delim = cell;
		format.line_delim = line;
		format.screen_sym = screen;
	}

	CsvIterator end() { return CsvIterator(false, *this); }
	~CsvParser() { delete line_tuple; }

};
