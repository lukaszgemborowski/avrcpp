#ifndef _AVRCPP_STD_CSTDINT_HPP_
#define _AVRCPP_STD_CSTDINT_HPP_

#include <stdint.h>

namespace std
{
    using int8_t = ::int8_t;
    using int16_t = ::int16_t;
    using int32_t = ::int32_t;
    using int64_t = ::int64_t;

    using uint8_t = ::uint8_t;
    using uint16_t = ::uint16_t;
    using uint32_t = ::uint32_t;
    using uint64_t = ::uint64_t;

    using intmax_t = uint64_t;
}

#endif // _AVRCPP_STD_CSTDINT_HPP_
