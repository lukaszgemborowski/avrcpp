#ifndef _AVRCPP_STD_NEW_H_
#define _AVRCPP_STD_NEW_H_

#include "cstddef.hpp"

inline void* operator new(std::size_t, void* __p) throw() { return __p; }
inline void  operator delete(void*, void*) throw() { }

#endif
