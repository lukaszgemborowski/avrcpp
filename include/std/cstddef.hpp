#ifndef _TOOLBOX_STD_CSTDDEF_HPP_
#define _TOOLBOX_STD_CSTDDEF_HPP_

#ifdef TOOLBOX_HAS_STDLIB
    #include <cstddef>
#else

#include <stddef.h>

namespace std
{
using size_t = ::size_t;
}

#endif

#endif // _TOOLBOX_STD_CSTDDEF_HPP_