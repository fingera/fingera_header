/**
 * @brief 安全释放内存
 *
 * @file cleanse.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-10
 */
#ifndef _FINGERA_HEADER_CLEANSE_H_
#define _FINGERA_HEADER_CLEANSE_H_

#include <stdlib.h>
#include <string.h>

#include <fingera/header/os.h>
#include <fingera/header/utility.h>

#if FINGERA_OS == FINGERA_OS_WINDOWS
#include <Windows.h>
#define cleanse SecureZeroMemory
#else
static inline void cleanse(void *ptr, size_t size) {
  memset(ptr, 0, size);
  __asm__ __volatile__("" : : "r"(ptr) : "memory");
}
#endif

static inline void *malloc_zero(size_t size) {
  void *ptr = malloc(size);
  memset(ptr, 0, size);
  return ptr;
}

static inline void free_se(void *ptr, size_t size) {
  cleanse(ptr, size);
  free(ptr);
}

#endif  // _FINGERA_HEADER_CLEANSE_H_