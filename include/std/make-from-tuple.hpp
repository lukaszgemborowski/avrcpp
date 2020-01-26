#ifndef AVRCPP_STD_MAKE_FROM_TUPLE_H
#define AVRCPP_STD_MAKE_FROM_TUPLE_H

#include "tuple.hpp"

namespace std
{

// reference: https://en.cppreference.com/w/cpp/utility/make_from_tuple
namespace detail {
template <class T, class Tuple, std::size_t... I>
constexpr T make_from_tuple_impl( Tuple&& t, std::index_sequence<I...> )
{
  return T(std::get<I>(std::forward<Tuple>(t))...);
}
} // namespace detail
 
template <class T, class Tuple>
constexpr T make_from_tuple( Tuple&& t )
{
    return detail::make_from_tuple_impl<T>(std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

} // namespace std

#endif // AVRCPP_STD_MAKE_FROM_TUPLE_H