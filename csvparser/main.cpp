#include <iostream>
#include <tuple>
#include <string>

template <typename ArgT>
void print_elem(ArgT& arg) {
    std::cout << arg << ", ";
}

template <typename TupleT, std::size_t... index>
void print_tuple_v1(TupleT& tuple, std::index_sequence<index...> ic) {
    (print_elem(std::get<index>(tuple)),...);
}

template <typename TupleT, std::size_t TupleSize = std::tuple_size_v<TupleT>>
void print_tuple_v2(TupleT& tuple) {
    print_tuple_v1(tuple, std::make_index_sequence<TupleSize>());
}

int main()
{
    std::tuple<std::string, int, double> test = { "HAHAHA, The JOKER's TRAP", 11, -1.222 };

    print_tuple_v1<decltype(test), 0, 1, 2>(test, std::index_sequence<0, 1, 2>());
    std::cout << '\n';
    print_tuple_v1(test, std::make_index_sequence<std::tuple_size<decltype(test)>::value>());
    std::cout << '\n';
    print_tuple_v1(test, std::make_index_sequence<std::tuple_size_v<decltype(test)>>());

    std::cout << '\n';
    print_tuple_v2(test);

}
