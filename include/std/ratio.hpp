#ifndef AVRCPP_STD_RATIO_HPP
#define AVRCPP_STD_RATIO_HPP

#include <cstdint>

namespace std
{

namespace detail
{
template<class T>
constexpr auto gcd(T a, T b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}

template<class T>
constexpr T sign(T a)
{
    if (a >= 0)
        return 1;
    else
        return -1;
}

template<class T>
constexpr T abs(T a)
{
    if (a >= 0)
        return a;
    else
        return -a;
}

} // namespace detail

template<intmax_t Num, intmax_t Denom = 1>
struct ratio {
    static constexpr intmax_t raw_num = Num;
    static constexpr intmax_t raw_den = Denom;

    static constexpr intmax_t num =
        detail::sign(Num) * detail::sign(Denom) * detail::abs(Num) / detail::gcd(Num, Denom);
    static constexpr intmax_t den =
        detail::abs(Denom) / detail::gcd(Num, Denom);

    using type = ratio<num, den>;
};

using kilo = ratio<1000, 1>;
using mega = ratio<1000000, 1>;
using giga = ratio<1000000000, 1>;

namespace ext
{
using kibi = ratio<intmax_t(1) << 10, 1>;
using mebi = ratio<intmax_t(1) << 20, 1>;
using gibi = ratio<intmax_t(1) << 30, 1>;
} // namespace std::ext

}

#endif // AVRCPP_STD_RATIO_HPP
