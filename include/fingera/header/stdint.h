/**
 * @brief 对VC特殊处理
 *
 * @file stdint_vc.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-11
 */
#ifndef _FINGERA_HEADER_STDINT_VC_H_
#define _FINGERA_HEADER_STDINT_VC_H_

#include <fingera/header/compiler.h>

#if FINGERA_COMPILER == FINGERA_COMPILER_MSVC && FINGERA_COMPILER_MAJOR < 11
typedef signed __int8 int8_t;
typedef signed __int16 int16_t;
typedef signed __int32 int32_t;
typedef signed __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#endif  // _FINGERA_HEADER_STDINT_VC_H_