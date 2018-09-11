/**
 * @brief 根据预定义宏识别当前编译器
 * FINGERA_COMPILER_CLANG
 * FINGERA_COMPILER_GCC
 * FINGERA_COMPILER_MSVC
 * FINGERA_COMPILER 当前编译器 如果未识别定义0
 * FINGERA_COMPILER_MAJOR 主版本号
 * FINGERA_COMPILER_MINOR 副版本号
 *
 * @file compiler.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-10
 */
#ifndef _FINGERA_HEADER_COMPILER_H_
#define _FINGERA_HEADER_COMPILER_H_

#define FINGERA_COMPILER_CLANG 1
#define FINGERA_COMPILER_GCC 2
#define FINGERA_COMPILER_MSVC 3

#if defined(__clang__)

#define FINGERA_COMPILER FINGERA_COMPILER_CLANG
#define FINGERA_COMPILER_MAJOR __clang_major__
#define FINGERA_COMPILER_MINOR __clang_minor__

#elif defined(__GNUC__)

#define FINGERA_COMPILER FINGERA_COMPILER_GCC
#define FINGERA_COMPILER_MAJOR __GNUC__
#define FINGERA_COMPILER_MINOR __GNUC_MINOR__

#elif defined(_MSC_VER)

#define FINGERA_COMPILER FINGERA_COMPILER_MSVC
#if (_MSC_VER > 1900)
#define FINGERA_COMPILER_MAJOR (_MSC_VER / 100)
#elif (_MSC_VER >= 1900)
#define FINGERA_COMPILER_MAJOR (_MSC_VER / 100 - 5)
#else
#define FINGERA_COMPILER_MAJOR (_MSC_VER / 100 - 6)
#endif
#define FINGERA_COMPILER_MINOR (_MSC_VER % 100)

#else

#define FINGERA_COMPILER 0
#define FINGERA_COMPILER_MAJOR 0
#define FINGERA_COMPILER_MINOR 0
#warning 没有识别编译器

#endif

#endif  // _FINGERA_HEADER_COMPILER_H_