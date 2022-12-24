#pragma once
#include <fstream>
#include <tuple>
#include <vector>

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
    os << " )";
    return os;
}

template<typename ArgT>
void read_token(std::string& str, std::size_t& pos_token_begin, void* place) {
    std::cout << pos_token_begin;
    pos_token_begin+=5;
    ArgT* ptr = new (place) ArgT;
    *ptr = 4;
}


template<typename... TupleTypes, std::size_t... index>
void assign_cell_tuple(std::tuple<TupleTypes...>& t, std::index_sequence<index...>, std::string& line) {
    std::vector<void*> cells;
    (cells.push_back(&std::get<index>(t)),...);
    std::size_t pos_next_cell = 0;
    /*
    for (void* cell : cells) {
        cell = read_token<TupleTypes>(line, pos_next_cell);
    }*/
    ((read_token<TupleTypes>(line, pos_next_cell, cells.at(index))), ...);
    //std::cout << cells[0];
}

template <typename... TupleTypes>
std::tuple<TupleTypes...>* read_tuple(std::ifstream& os, std::tuple<TupleTypes...>* t, Format& format) {
    std::string line;   
    getline(os, line, format.line_delim);
    delete_sym(line, format.screen_sym);

    std::size_t pos_next_cell = 0;
    std::size_t pos_tuple = 0;
    //(assign_cell_tuple(*t, pos_tuple++, read_token<TupleTypes>(line, pos_next_cell)), ...);
    assign_cell_tuple(*t, std::index_sequence_for<TupleTypes...>(), line);


    //std::cout << typeid( std::make_tuple( (read_token<TupleTypes>(line, next_cell_pos), ...) ) ).name();
    //std::cout << std::make_tuple((read_token<TupleTypes>(line, next_cell_pos), ...));

    return t;
}

template <typename Ch, class Tr, typename... ArgsT>
auto& operator>>(std::basic_ostream<Ch, Tr>& os, const std::tuple<ArgsT...>& t) {
    read_tuple(os, t);
    return os;
}
