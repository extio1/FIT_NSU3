#pragma once
#include <tuple>
#include <fstream>

template <typename... TupleTypes>
class CsvParser {
public:
	explicit CsvParser(std::ifstream& f, const int skip = 0) : input_stream(f) { for(int i = 0; i < skip; i++) ignore(); }
	
	class CsvIterator : public std::iterator<std::input_iterator_tag, std::tuple<TupleTypes...>> {
	public:
		CsvIterator(const bool s) : state(s), line_tuple(new std::tuple<TupleTypes... >) {}

		CsvIterator(const CsvIterator& other): state(other.state) {
			line_tuple = new std::tuple<TupleTypes... >;
			*line_tuple = other->line_tuple;
		}

		CsvIterator& operator=(const CsvIterator& other) { 
			if (this != &other) {
				state = other.state;
				*line_tuple = other->line_tuple;
			}
		}

		CsvIterator& operator++() { 
			read_next(); 
		}
		CsvIterator operator++(int) { 
			CsvIterator temp(*this); ++(*this); return temp; 
		}

		bool operator==(const CsvIterator& other) {
			if (state != other.state)
				return false;
			if (*line_tuple != other->line_tuple)
				return false;
			return true;
		}
		bool operator!=(const CsvIterator& other) { 
			return !(*this == other); 
		}

		~CsvIterator() { delete line_tuple; }
	private:
		std::tuple<TupleTypes...>* line_tuple;
		std::string line_str;
		bool state; // state = 1 : there's something to read. 
					// state = 0 : the end of file has been reached

		void read_next() {
			std::getline(input_stream, line_str);
			if (input_stream.eof())
				return 0;
			parse_line();
			return 1;
		}
		void parse_line() {

		}
	};

	CsvIterator begin() { return CsvIterator(true); }
	CsvIterator end() { return CsvIterator(false); }
private:
	std::ifstream input_stream;
};
