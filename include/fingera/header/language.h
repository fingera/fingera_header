/**
 * @brief 根据语言定义下面的宏
 * FINGERA_EXTERN_C
 * FINGERA_EXTERN_C_BEGIN
 * FINGERA_EXTERN_C_END
 *
 * @file language.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-10
 */
#ifndef _FINGERA_HEADER_LANGUAGE_H_
#define _FINGERA_HEADER_LANGUAGE_H_

#if defined(__cplusplus)

#define FINGERA_EXTERN_C extern "C"
#define FINGERA_EXTERN_C_BEGIN extern "C" {
#define FINGERA_EXTERN_C_END }

#else  // defined(__cplusplus)

#define FINGERA_EXTERN_C
#define FINGERA_EXTERN_C_BEGIN
#define FINGERA_EXTERN_C_END

#endif  // defined(__cplusplus)

#endif  // _FINGERA_HEADER_LANGUAGE_H_