#ifndef AVRCPP_LIMITS_HPP
#define AVRCPP_LIMITS_HPP

#include <limits.h>

namespace std
{

template<class T> struct numeric_limits
{
    static constexpr bool is_specialized = false;
};

template<> struct numeric_limits<int>
{
    static constexpr bool is_specialized    = true;
    static constexpr bool is_signed         = true;
    static constexpr bool is_integer        = true;
    static constexpr bool is_exact          = true;
    static constexpr bool has_infinity      = false;
    // has_quiet_NaN
    // has_signaling_NaN
    // has_denorm
    // has_denorm_loss
    // round_style
    // is_iec559
    // is_bounded
    // is_modulo
    // digits
    // digits10
    // max_digits10
    // radix
    // min_exponent
    // min_exponent10
    // max_exponent
    // max_exponent10
    // traps
    // tinyness_before

    static constexpr int min() noexcept       { return INT_MIN; }
    static constexpr int lowest() noexcept    { return INT_MIN; }
    static constexpr int max() noexcept       { return INT_MAX; }
    // static constexpr T epsilon() noexcept;
    // static constexpr T round_error() noexcept;
    // static constexpr T infinity() noexcept;
    // static constexpr T quiet_NaN() noexcept;
    // static constexpr T signaling_NaN() noexcept;
    // static constexpr T denorm_min() noexcept;
};

template<> struct numeric_limits<unsigned int>
{
    static constexpr bool is_specialized    = true;
    static constexpr bool is_signed         = false;
    static constexpr bool is_integer        = true;
    static constexpr bool is_exact          = true;
    static constexpr bool has_infinity      = false;
    // has_quiet_NaN
    // has_signaling_NaN
    // has_denorm
    // has_denorm_loss
    // round_style
    // is_iec559
    // is_bounded
    // is_modulo
    // digits
    // digits10
    // max_digits10
    // radix
    // min_exponent
    // min_exponent10
    // max_exponent
    // max_exponent10
    // traps
    // tinyness_before

    static constexpr unsigned int min() noexcept       { return 0; }
    static constexpr unsigned int lowest() noexcept    { return 0; }
    static constexpr unsigned int max() noexcept       { return UINT_MAX; }
    // static constexpr T epsilon() noexcept;
    // static constexpr T round_error() noexcept;
    // static constexpr T infinity() noexcept;
    // static constexpr T quiet_NaN() noexcept;
    // static constexpr T signaling_NaN() noexcept;
    // static constexpr T denorm_min() noexcept;
};

} // namespace std

#endif // AVRCPP_LIMITS_HPP