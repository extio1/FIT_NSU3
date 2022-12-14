#pragma once
#include <fstream>
#include <tuple>

template <class Ch, class Tr, typename TupleT, std::size_t... index>
void print_tuple(std::basic_ostream<Ch, Tr>& os, TupleT& tuple, std::index_sequence<index...> is) {
    ((os << std::get<index>(tuple) << ((index < size(is) - 1) ? ", " : " ")), ...);
}

template <class Ch, class Tr, typename... ArgsT>
auto& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<ArgsT...>& t) {
    os << "( ";
    print_tuple(os, t, std::index_sequence_for<ArgsT...>());
    os << " )";
    return os;
}
