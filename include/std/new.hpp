#ifndef _TOOLBOX_STD_NEW_H_
#define _TOOLBOX_STD_NEW_H_

#ifdef TOOLBOX_HAS_STDLIB
#include <new>
#else
#include "cstddef.hpp"
inline void* operator new(std::size_t, void* __p) throw() { return __p; }
inline void  operator delete(void*, void*) throw() { }
#endif

#endif