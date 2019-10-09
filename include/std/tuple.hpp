#ifndef _AVRCPP_CONTAINER_TUPLE_HPP_
#define _AVRCPP_CONTAINER_TUPLE_HPP_

#include "type_traits.hpp"
#include "utility.hpp"

namespace std
{

template<int I, class T>
struct tuple_node
{
    template<class U>
    constexpr tuple_node(U&& value)
        : value(std::forward<U>(value))
    {}

    constexpr tuple_node()
        : value{}
    {}

    T value;
};

template<
    class Indices,
    class... Types>
struct tuple_storage;

template<std::size_t... Indices, class... Types>
struct tuple_storage<std::integer_sequence<std::size_t, Indices...>, Types...>
    : tuple_node<Indices, Types>...
{
    constexpr tuple_storage() {}

    template<class... Items>
    constexpr tuple_storage(Items&&... items)
        : tuple_node<Indices, Types>(std::forward<Items>(items))...
    {}
};

template<class... Types>
struct tuple
{
    tuple_storage<std::make_integer_sequence<std::size_t, sizeof...(Types)>, Types...> storage;
    using size = std::integral_constant<std::size_t, sizeof...(Types)>;


    constexpr tuple() {}

    template<class... Items>
    constexpr tuple(Items&&... items)
        : storage{std::forward<Items>(items)...}
    {}
};

template<class tup>
struct first_t;

template<class First, class... Tail>
struct first_t<tuple<First, Tail...>>
{
    using type = First;
    using tail = tuple<Tail...>;
};

namespace detail
{
template<int Count, class Tuple>
struct type_of
{
    using result = typename type_of<
        Count - 1,
        typename first_t<Tuple>::tail
    >::result;
};

template<class Tuple>
struct type_of<0, Tuple>
{
    using result = typename first_t<Tuple>::type;
};

} // namespace detail

template<int Index, class Tuple>
struct type_of
{
    using type = typename detail::type_of<Index, Tuple>::result;
};

namespace detail
{
template<int Index, int Size, class Type, class Tuple>
struct index_of
{
    using type = typename toolbox::type_of<Index, Tuple>::type;

    using value_t =
        std::conditional_t<
            std::is_same<type, Type>::value,
            std::integral_constant<std::size_t, Index>,
            typename index_of<Index + 1, Size, Type, Tuple>::value_t
        >;

    static constexpr std::size_t value = value_t::value;
};

template<int Size, class Type, class Tuple>
struct index_of<Size, Size, Type, Tuple>
{
    // may be defined as Size as static_cast will fail anyway
    using value_t = std::integral_constant<std::size_t, Size>;
    static constexpr std::size_t value = Size;
};


} // namespace detail

template<class T, class Tuple>
constexpr auto& get(Tuple &t)
{
    return static_cast<
        tuple_node<detail::index_of<0, Tuple::size::value, T, Tuple>::value, T> *>(&t.storage)->value;
}

template<int Index, class Tuple>
constexpr auto& get(Tuple &t)
{
    return static_cast<
        tuple_node<Index, typename type_of<Index, Tuple>::type> *>(&t.storage)->value;
}



template<class... Args>
constexpr auto make_tuple(Args&&... args)
{
    return tuple<std::decay_t<Args>...>(std::forward<Args>(args)...);
}

} // namespace std

#endif // _AVRCPP_CONTAINER_TUPLE_HPP_
