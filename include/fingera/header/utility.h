/**
 * @brief 一些有用的宏
 * _countof_
 *
 * @file utility.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-11
 */
#ifndef _FINGERA_HEADER_UTILITY_H_
#define _FINGERA_HEADER_UTILITY_H_

#include <fingera/header/compiler.h>

#ifndef _countof_
#define _countof_(x) (sizeof(x) / sizeof(x[0]))
#endif

#ifndef _unused_
#define _unused_(x) (void)x;
#endif

#if FINGERA_COMPILER == FINGERA_COMPILER_MSVC && FINGERA_COMPILER_MAJOR <= 12
#ifndef inline
#define inline __inline
#endif  // inline
#endif

#endif  // _FINGERA_HEADER_UTILITY_H_