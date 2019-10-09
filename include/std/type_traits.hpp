#ifndef _TOOLBOX_STD_TYPE_TRAITS_H_
#define _TOOLBOX_STD_TYPE_TRAITS_H_

#include <toolbox/config.h>

#ifdef TOOLBOX_HAS_STDLIB
    #include <type_traits>
#else

#include "cstddef.hpp"

namespace std
{
template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant type;
    constexpr operator value_type() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/remove_reference
template< class T > struct remove_reference      {typedef T type;};
template< class T > struct remove_reference<T&>  {typedef T type;};
template< class T > struct remove_reference<T&&> {typedef T type;};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/conditional
template<bool B, class T, class F>
struct conditional { typedef T type; };
 
template<class T, class F>
struct conditional<false, T, F> { typedef F type; };

template<bool B, class T, class F>
using conditional_t = typename conditional<B, T, F>::type;

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/is_array
template<class T>
struct is_array : std::false_type {};
 
template<class T>
struct is_array<T[]> : std::true_type {};
 
template<class T, std::size_t N>
struct is_array<T[N]> : std::true_type {};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/remove_extent
template<class T>
struct remove_extent { typedef T type; };
 
template<class T>
struct remove_extent<T[]> { typedef T type; };
 
template<class T, std::size_t N>
struct remove_extent<T[N]> { typedef T type; };

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/is_function
// primary template
template<class>
struct is_function : std::false_type { };
 
// specialization for regular functions
template<class Ret, class... Args>
struct is_function<Ret(Args...)> : std::true_type {};
 
// specialization for variadic functions such as std::printf
template<class Ret, class... Args>
struct is_function<Ret(Args......)> : std::true_type {};
 
// specialization for function types that have cv-qualifiers
template<class Ret, class... Args>
struct is_function<Ret(Args...) const> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) volatile> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) const volatile> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) const> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) volatile> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) const volatile> : std::true_type {};
 
// specialization for function types that have ref-qualifiers
template<class Ret, class... Args>
struct is_function<Ret(Args...) &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) const &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) volatile &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) const volatile &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) const &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) volatile &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) const volatile &> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) const &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) volatile &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args...) const volatile &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) const &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) volatile &&> : std::true_type {};
template<class Ret, class... Args>
struct is_function<Ret(Args......) const volatile &&> : std::true_type {};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/add_pointer
namespace detail {
template< class T, bool is_function_type = false >
struct add_pointer {
    using type = typename std::remove_reference<T>::type*;
};
 
template< class T >
struct add_pointer<T, true> {
    using type = T;
};
 
template< class T, class... Args >
struct add_pointer<T(Args...), true> {
    using type = T(*)(Args...);
};
 
template< class T, class... Args >
struct add_pointer<T(Args..., ...), true> {
    using type = T(*)(Args..., ...);
};
 
} // namespace detail
 
template< class T >
struct add_pointer : detail::add_pointer<T, std::is_function<T>::value> {};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/remove_cv
template< class T > struct remove_const          { typedef T type; };
template< class T > struct remove_const<const T> { typedef T type; };
 
template< class T > struct remove_volatile             { typedef T type; };
template< class T > struct remove_volatile<volatile T> { typedef T type; };

template< class T >
struct remove_cv {
    typedef typename std::remove_volatile<typename std::remove_const<T>::type>::type type;
};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/decay
template< class T >
struct decay {
private:
    typedef typename std::remove_reference<T>::type U;
public:
    typedef typename std::conditional< 
        std::is_array<U>::value,
        typename std::remove_extent<U>::type*,
        typename std::conditional< 
            std::is_function<U>::value,
            typename std::add_pointer<U>::type,
            typename std::remove_cv<U>::type
        >::type
    >::type type;
};

template<class T>
using decay_t = typename std::decay<T>::type;

// --------------------------------------------------------------
// https://stackoverflow.com/questions/7510182/how-does-stdmove-transfer-values-into-rvalues
template <typename T>
typename remove_reference<T>::type&& move(T&& arg)
{
  return static_cast<typename remove_reference<T>::type&&>(arg);
}

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/memory/addressof
template< class T >
T* addressof(T& arg) 
{
    return reinterpret_cast<T*>(
               &const_cast<char&>(
                  reinterpret_cast<const volatile char&>(arg)));
}

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

template <class T>
class reference_wrapper {
public:
  // types
  typedef T type;
 
  // construct/copy/destroy
  reference_wrapper(T& ref) noexcept : _ptr(std::addressof(ref)) {}
  reference_wrapper(T&&) = delete;
  reference_wrapper(const reference_wrapper&) noexcept = default;
 
  // assignment
  reference_wrapper& operator=(const reference_wrapper& x) noexcept = default;
 
  // access
  operator T& () const noexcept { return *_ptr; }
  T& get() const noexcept { return *_ptr; }
 
private:
  T* _ptr;
};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/is_same
template<class T, class U>
struct is_same : std::false_type {};
 
template<class T>
struct is_same<T, T> : std::true_type {};

template< class T, class U >
constexpr bool is_same_v = is_same<T, U>::value;

// --------------------------------------------------------------
// http://www.cplusplus.com/forum/general/219156/
template<typename T>
struct add_rvalue_reference
{
   using gtype = T&&;
};

template<typename T>
struct add_rvalue_reference<T&>
{
   using type = T&;
};

template<typename T>
struct add_lvalue_reference
{
   using type = T&;
};

// --------------------------------------------------------------
// https://www.boost.org/doc/libs/1_53_0/boost/utility/declval.hpp
template <typename T>
typename add_rvalue_reference<T>::type declval();

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/void_t
template< class... >
using void_t = void;

// --------------------------------------------------------------
// https://www.boost.org/doc/libs/1_67_0/boost/type_traits/is_union.hpp
template <class T> struct is_union : public integral_constant<bool, __is_union(T)> {};
template <class T> struct is_union<T const> : public is_union<T>{};
template <class T> struct is_union<T volatile const> : public is_union<T>{};
template <class T> struct is_union<T volatile> : public is_union<T>{};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/is_class
namespace detail {
    template <class T> char test(int T::*);
    struct two { char c[2]; };
    template <class T> two test(...);
}
 
template <class T>
struct is_class : std::integral_constant<bool, sizeof(detail::test<T>(0))==1
                                            && !std::is_union<T>::value> {};

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/is_base_of
namespace details {
    template <typename Base> std::true_type is_base_of_test_func(const volatile Base*);
    template <typename Base> std::false_type is_base_of_test_func(const volatile void*);
    template <typename Base, typename Derived>
    using pre_is_base_of = decltype(is_base_of_test_func<Base>(std::declval<Derived*>()));
 
    // with <experimental/type_traits>:
    // template <typename Base, typename Derived>
    // using pre_is_base_of2 = std::experimental::detected_or_t<std::true_type, pre_is_base_of, Base, Derived>;
    template <typename Base, typename Derived, typename = void>
    struct pre_is_base_of2 : public std::true_type { };
    // note std::void_t is a C++17 feature
    template <typename Base, typename Derived>
    struct pre_is_base_of2<Base, Derived, std::void_t<pre_is_base_of<Base, Derived>>> :
        public pre_is_base_of<Base, Derived> { };
}
 
template <typename Base, typename Derived>
struct is_base_of :
    public std::conditional_t<
        std::is_class<Base>::value && std::is_class<Derived>::value,
        details::pre_is_base_of2<Base, Derived>,
        std::false_type
    > { };

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/add_cv
template< class T >
struct add_cv { typedef const volatile T type; };
 
template< class T> struct add_const { typedef const T type; };
 
template< class T> struct add_volatile { typedef volatile T type; };

// --------------------------------------------------------------
// https://en.cppreference.com/w/cpp/types/aligned_storage
template<std::size_t Len, std::size_t Align /* default alignment not implemented */>
struct aligned_storage {
    struct type {
        alignas(Align) unsigned char data[Len];
    };
};

}

#endif // TOOLBOX_HAS_STDLIB

#endif