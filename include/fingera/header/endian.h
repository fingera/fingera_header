/**
 * @brief 根据目标系统和编译器识别出大小端 并定义相关的转换函数
 *
 * @file endian.h
 * @author liuyujun@fingera.cn
 * @date 2018-09-10
 */
#ifndef _FINGERA_HEADER_ENDIAN_H_
#define _FINGERA_HEADER_ENDIAN_H_

#include <stddef.h>
#include <string.h>

#include <fingera/header/language.h>
#include <fingera/header/os.h>
#include <fingera/header/stdint.h>
#include <fingera/header/utility.h>

FINGERA_EXTERN_C_BEGIN

#if (FINGERA_OS == FINGERA_OS_ANDROID) || (FINGERA_OS == FINGERA_OS_LINUX)
#include <endian.h>

#elif (FINGERA_OS == FINGERA_OS_IOS) || (FINGERA_OS == FINGERA_OS_OSX)
#include <libkern/OSByteOrder.h>
#define htobe16(x) OSSwapHostToBigInt16(x)
#define htole16(x) OSSwapHostToLittleInt16(x)
#define be16toh(x) OSSwapBigToHostInt16(x)
#define le16toh(x) OSSwapLittleToHostInt16(x)
#define htobe32(x) OSSwapHostToBigInt32(x)
#define htole32(x) OSSwapHostToLittleInt32(x)
#define be32toh(x) OSSwapBigToHostInt32(x)
#define le32toh(x) OSSwapLittleToHostInt32(x)
#define htobe64(x) OSSwapHostToBigInt64(x)
#define htole64(x) OSSwapHostToLittleInt64(x)
#define be64toh(x) OSSwapBigToHostInt64(x)
#define le64toh(x) OSSwapLittleToHostInt64(x)
#define __BYTE_ORDER BYTE_ORDER
#define __BIG_ENDIAN BIG_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __PDP_ENDIAN PDP_ENDIAN

#elif (FINGERA_OS == FINGERA_OS_WINDOWS)
#include <stdlib.h>

#if (BYTE_ORDER == LITTLE_ENDIAN)
#define htobe16(x) _byteswap_ushort(x)
#define htole16(x) (x)
#define be16toh(x) _byteswap_ushort(x)
#define le16toh(x) (x)
#define htobe32(x) _byteswap_ulong(x)
#define htole32(x) (x)
#define be32toh(x) _byteswap_ulong(x)
#define le32toh(x) (x)
#define htobe64(x) _byteswap_uint64(x)
#define htole64(x) (x)
#define be64toh(x) _byteswap_uint64(x)
#define le64toh(x) (x)
#else
#define htobe16(x) (x)
#define htole16(x) _byteswap_ushort(x)
#define be16toh(x) (x)
#define le16toh(x) _byteswap_ushort(x)
#define htobe32(x) (x)
#define htole32(x) _byteswap_ulong(x)
#define be32toh(x) (x)
#define le32toh(x) _byteswap_ulong(x)
#define htobe64(x) (x)
#define htole64(x) _byteswap_uint64(x)
#define be64toh(x) (x)
#define le64toh(x) _byteswap_uint64(x)
#endif

#define __BYTE_ORDER BYTE_ORDER
#define __BIG_ENDIAN BIG_ENDIAN
#define __LITTLE_ENDIAN LITTLE_ENDIAN
#define __PDP_ENDIAN PDP_ENDIAN

#else
#error 无法识别字节序

#endif

static inline uint16_t readle16(const void *buf) {
  uint16_t value;
  memcpy(&value, buf, sizeof(value));
  return le16toh(value);
}
static inline uint32_t readle32(const void *buf) {
  uint32_t value;
  memcpy(&value, buf, sizeof(value));
  return le32toh(value);
}
static inline uint64_t readle64(const void *buf) {
  uint64_t value;
  memcpy(&value, buf, sizeof(value));
  return le64toh(value);
}

static inline uint16_t readbe16(const void *buf) {
  uint16_t value;
  memcpy(&value, buf, sizeof(value));
  return be16toh(value);
}
static inline uint32_t readbe32(const void *buf) {
  uint32_t value;
  memcpy(&value, buf, sizeof(value));
  return be32toh(value);
}
static inline uint64_t readbe64(const void *buf) {
  uint64_t value;
  memcpy(&value, buf, sizeof(value));
  return be64toh(value);
}

static inline void writele16(void *buf, uint16_t value) {
  value = htole16(value);
  memcpy(buf, &value, sizeof(value));
}
static inline void writele32(void *buf, uint32_t value) {
  value = htole32(value);
  memcpy(buf, &value, sizeof(value));
}
static inline void writele64(void *buf, uint64_t value) {
  value = htole64(value);
  memcpy(buf, &value, sizeof(value));
}

static inline void writebe16(void *buf, uint16_t value) {
  value = htobe16(value);
  memcpy(buf, &value, sizeof(value));
}
static inline void writebe32(void *buf, uint32_t value) {
  value = htobe32(value);
  memcpy(buf, &value, sizeof(value));
}
static inline void writebe64(void *buf, uint64_t value) {
  value = htobe64(value);
  memcpy(buf, &value, sizeof(value));
}

FINGERA_EXTERN_C_END

#if defined(__cplusplus)

static inline uint8_t htobe(uint8_t v) { return v; }
static inline uint16_t htobe(uint16_t v) { return htobe16(v); }
static inline uint32_t htobe(uint32_t v) { return htobe32(v); }
static inline uint64_t htobe(uint64_t v) { return htobe64(v); }
static inline uint8_t htole(uint8_t v) { return v; }
static inline uint16_t htole(uint16_t v) { return htole16(v); }
static inline uint32_t htole(uint32_t v) { return htole32(v); }
static inline uint64_t htole(uint64_t v) { return htole64(v); }
static inline uint8_t betoh(uint8_t v) { return v; }
static inline uint16_t betoh(uint16_t v) { return be16toh(v); }
static inline uint32_t betoh(uint32_t v) { return be32toh(v); }
static inline uint64_t betoh(uint64_t v) { return be64toh(v); }
static inline uint8_t letoh(uint8_t v) { return v; }
static inline uint16_t letoh(uint16_t v) { return le16toh(v); }
static inline uint32_t letoh(uint32_t v) { return le32toh(v); }
static inline uint64_t letoh(uint64_t v) { return le64toh(v); }

static inline int8_t htobe(int8_t v) { return v; }
static inline int16_t htobe(int16_t v) { return htobe16(v); }
static inline int32_t htobe(int32_t v) { return htobe32(v); }
static inline int64_t htobe(int64_t v) { return htobe64(v); }
static inline int8_t htole(int8_t v) { return v; }
static inline int16_t htole(int16_t v) { return htole16(v); }
static inline int32_t htole(int32_t v) { return htole32(v); }
static inline int64_t htole(int64_t v) { return htole64(v); }
static inline int8_t betoh(int8_t v) { return v; }
static inline int16_t betoh(int16_t v) { return be16toh(v); }
static inline int32_t betoh(int32_t v) { return be32toh(v); }
static inline int64_t betoh(int64_t v) { return be64toh(v); }
static inline int8_t letoh(int8_t v) { return v; }
static inline int16_t letoh(int16_t v) { return le16toh(v); }
static inline int32_t letoh(int32_t v) { return le32toh(v); }
static inline int64_t letoh(int64_t v) { return le64toh(v); }

template <typename T>
static inline T readbe(const void *buf) {
  T value;
  memcpy(&value, buf, sizeof(value));
  return betoh(value);
}
template <typename T>
static inline T readle(const void *buf) {
  T value;
  memcpy(&value, buf, sizeof(value));
  return letoh(value);
}
template <typename T>
static inline void writebe(void *buf, T value) {
  value = htobe(value);
  memcpy(buf, &value, sizeof(value));
}
template <typename T>
static inline void writele(void *buf, T value) {
  value = htole(value);
  memcpy(buf, &value, sizeof(value));
}

#endif

#endif  // _FINGERA_HEADER_ENDIAN_H_