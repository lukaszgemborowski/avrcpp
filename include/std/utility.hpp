#ifndef _TOOLBOX_STD_UTILITY_H_
#define _TOOLBOX_STD_UTILITY_H_

#include <toolbox/config.h>

#ifdef TOOLBOX_HAS_STDLIB
    #include <utility>
#else

#include "type_traits.hpp"

namespace std
{

// --------------------------------------------------------------
// https://stackoverflow.com/questions/27501400/the-implementation-of-stdforward
template <class T>
inline T&& forward(typename std::remove_reference<T>::type& t) noexcept
{
    return static_cast<T&&>(t);
}

template <class T>
inline T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{
    //static_assert(!std::is_lvalue_reference<T>::value,
    //              "Can not forward an rvalue as an lvalue.");
    return static_cast<T&&>(t);
}

// --------------------------------------------------------------
template <class T, T... Ints>
struct integer_sequence
{
    using type = integer_sequence;
    using value_type = T;
    static constexpr std::size_t size() noexcept { return sizeof...(Ints); }
};

// --------------------------------------------------------------

template <class T, class Sequence1, class Sequence2>
struct _merge_and_renumber;

template <class T, size_t... I1, size_t... I2>
struct _merge_and_renumber<T, integer_sequence<T, I1...>, integer_sequence<T, I2...>>
    : public integer_sequence<T, I1..., (sizeof...(I1)+I2)...>
{
};

// --------------------------------------------------------------

template <class T, size_t N>
struct make_integer_sequence_impl
    : _merge_and_renumber<T, typename make_integer_sequence_impl<T, N/2>::type,
                        typename make_integer_sequence_impl<T, N - N/2>::type>
{
    using type = typename _merge_and_renumber<T, typename make_integer_sequence_impl<T, N/2>::type,
                        typename make_integer_sequence_impl<T, N - N/2>::type>::type;
};

template<class T> struct make_integer_sequence_impl<T, 0> : integer_sequence<T> {
    using type = integer_sequence<T>;
};
template<class T> struct make_integer_sequence_impl<T, 1> : integer_sequence<T, 0> {
    using type = integer_sequence<T, 0>;
};

template<class T, T N>
using make_integer_sequence = typename make_integer_sequence_impl<T, N>::type;

}

#endif // TOOLBOX_HAS_STDLIB

#endif // _TOOLBOX_STD_UTILITY_H_