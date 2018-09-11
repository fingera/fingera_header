/**
 * @brief 安全释放内存
 *
 * @file cleanse.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-10
 */
#ifndef _FINGERA_HEADER_CLEANSE_H_
#define _FINGERA_HEADER_CLEANSE_H_

#include <fingera/header/os.h>
#include <fingera/header/utility.h>

#if FINGERA_OS == FINGERA_OS_WINDOWS
#include <Windows.h>
#define cleanse SecureZeroMemory
#else
#include <string.h>
static inline void cleanse(void *ptr, size_t size) {
  memset(ptr, 0, size);
  __asm__ __volatile__("" : : "r"(ptr) : "memory");
}
#endif

// void explicit_bzero(void *b, size_t len);

#endif  // _FINGERA_HEADER_CLEANSE_H_