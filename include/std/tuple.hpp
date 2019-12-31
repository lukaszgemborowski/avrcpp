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
    constexpr tuple_storage(tuple_storage &&) = default;

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
    constexpr tuple(tuple &&) = default;

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
    using type = typename std::type_of<Index, Tuple>::type;

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

template<class T>
struct tuple_size;

template<class... Types>
struct tuple_size<std::tuple<Types...>>
    : std::integral_constant<std::size_t, sizeof...(Types)>
{};

namespace detail
{
template<class... A>
struct t_type;

template<class... A, class... B>
struct t_type<std::tuple<A...>, std::tuple<B...>>
{
    using result_t = std::tuple<A..., B...>;
    using a_type = std::tuple<A...>;
    static constexpr auto a_size = sizeof...(A);
    using b_type = std::tuple<B...>;
    static constexpr auto b_size = sizeof...(B);

    template<std::size_t I>
    static auto&& get_one(a_type &&a, b_type &&b)
    {
        if constexpr (I < a_size)
            return std::get<I>(a);
        if constexpr (I >= a_size)
            return std::get<I - a_size>(b);
    }

    template<std::size_t... Idx>
    static auto cat(a_type &&a, b_type &&b, std::index_sequence<Idx...>)
    {
        return result_t {
                get_one<Idx>(
                std::forward<a_type>(a),
                std::forward<b_type>(b)
            )...
        };
    }

    static auto cat(a_type &&a, b_type &&b)
    {
        return cat(
            std::forward<a_type>(a),
            std::forward<b_type>(b),
            std::make_index_sequence<a_size + b_size>{}
        );
    }
};

template<class A>
struct t_type<A>
{
    using result_t = A;
};

template<class A, class... Tail>
struct t_type<A, Tail...>
{
    using result_t =
        typename t_type<A, typename t_type<Tail...>::result_t>::result_t;
};

} // namespace detail

template<class A>
auto tuple_cat(A &&a)
{
    return a;
}

template<class A, class... Ts>
auto tuple_cat(A &&a, Ts&&... tuples)
{
    using tail_result_t = typename detail::t_type<Ts...>::result_t;

    return detail::t_type<A, tail_result_t>::cat(
        std::forward<A>(a),
        tuple_cat(std::forward<Ts>(tuples)...)
    );
}

} // namespace std

#endif // _AVRCPP_CONTAINER_TUPLE_HPP_
