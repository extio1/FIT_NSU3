#pragma once
#include <fstream>
#include <tuple>
#include <vector>
#include <sstream>
#include "excpts.h"

struct Format {
    char cell_delim;
    char line_delim;
    char screen_sym;
    Format(char a, char b, char c) : cell_delim(a), line_delim(b), screen_sym(c) {}
};


inline void delete_sym(std::string& str, char sym) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] == sym)
            str.erase(i, 1);
}

template <typename Ch, class Tr, typename TupleT, std::size_t... index>
void print_tuple(std::basic_ostream<Ch, Tr>& os, TupleT& tuple, std::index_sequence<index...> is) {
    ((os << std::get<index>(tuple) << ((index < size(is) - 1) ? ", " : " ")), ...);
}

template <typename Ch, class Tr, typename... ArgsT>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<ArgsT...>& t) {
    os << "( ";
    print_tuple(os, t, std::index_sequence_for<ArgsT...>());
    os << ")";
    return os;
}

template<typename ArgT>
void read_token(const std::string& token_str, void* place, std::size_t col) {
    std::stringstream strst;
    strst << token_str;

    ArgT new_arg;
    strst >> new_arg;

    std::stringstream check_ss;
    check_ss << new_arg;

    if (token_str.size() != check_ss.str().size()) {
        throw cell_error(col+1);
    }

    ArgT* ptr = new (place) ArgT;
    *ptr = new_arg;
}

std::string parse_line(std::string& line, char delim, std::size_t& pos_token_begin) {
    std::string token_str;
    std::size_t sym_counter = 0;
    if (line != "") {
        std::size_t pos_token_end = pos_token_begin;
        while (pos_token_end < line.size() && line[pos_token_end] != delim) {
            pos_token_end++;
            sym_counter++;
        }
        token_str = line.substr(pos_token_begin, pos_token_end - pos_token_begin);
        pos_token_begin = pos_token_end + 1;
    }
    return token_str;
}

template<typename... TupleTypes, std::size_t... index>
void assign_cell_tuple(std::tuple<TupleTypes...>& t, std::index_sequence<index...>, std::string& line, Format& format) {
    std::vector<void*> cells;
    (cells.push_back(&std::get<index>(t)),...);

    std::size_t pos_next_cell = 0;
    ((read_token<TupleTypes>(parse_line(line, format.cell_delim, pos_next_cell), cells.at(index), pos_next_cell)), ...);
}

template <typename... TupleTypes>
std::tuple<TupleTypes...>* read_tuple(std::ifstream& os, std::tuple<TupleTypes...>* t, Format& format) {
    std::string line;   
    getline(os, line, format.line_delim);
    delete_sym(line, format.screen_sym);

    if (line == "")
        throw cell_error(0);

    assign_cell_tuple(*t, std::index_sequence_for<TupleTypes...>(), line, format);

    return t;
}

template <typename Ch, class Tr, typename... ArgsT>
auto& operator>>(std::basic_ostream<Ch, Tr>& os, const std::tuple<ArgsT...>& t) {
    read_tuple(os, t);
    return os;
}
