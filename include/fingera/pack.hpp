/**
 * @brief 二进制序列化
 *
 * @file pack.hpp
 * @author liuyujun@fingera.cn
 * @date 2018-09-18
 */
#pragma once

#include <type_traits>
#include <utility>

#include <fingera/header/endian.h>
#include <fingera/reflect.hpp>

namespace fingera {

template <typename Stream, typename T>
static inline void pack(Stream &s, const T &value);

template <typename Stream, typename T>
static inline void unpack(Stream &s, T &value);

namespace pack_detail {
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename IsInteger = void>
class if_arithmetic {
 public:
  template <typename Stream>
  static inline void pack(Stream &s, const T &value) {
    s << value;
  }
  template <typename Stream>
  static inline void unpack(Stream &s, T &value) {
    s >> value;
  }
};
template <typename T>
class if_arithmetic<
    T, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
 public:
  template <typename Stream>
  static inline void pack(Stream &s, const T &value) {
    const T le = htole(value);
    s.write(&le, sizeof(le));
  }
  template <typename Stream>
  static inline void unpack(Stream &s, T &value) {
    T le;
    s.read(&le, sizeof(le));
    value = letoh(le);
  }
};
////////////////////////////////////////////////////////////////////////////////
template <typename T, typename IsRefected = void>
class if_reflected {
 public:
  template <typename Stream>
  static inline void pack(Stream &s, const T &value) {
    if_arithmetic<T>::pack(s, value);
  }
  template <typename Stream>
  static inline void unpack(Stream &s, T &value) {
    if_arithmetic<T>::unpack(s, value);
  }
};
template <typename Stream, typename T>
class pack_reflect_visitor {
 private:
  const T &_object;
  Stream &_stream;

 public:
  inline pack_reflect_visitor(Stream &s, const T &object)
      : _object(object), _stream(s) {}

  template <typename Getter>
  inline void visit(const char *name) {
    ::fingera::pack(_stream, Getter::get(_object));
  }
};
template <typename Stream, typename T>
class unpack_reflect_visitor {
 private:
  T &_object;
  Stream &_stream;

 public:
  inline unpack_reflect_visitor(Stream &s, T &object)
      : _object(object), _stream(s) {}

  template <typename Setter>
  inline void visit(const char *name) {
    typename Setter::type tmp;
    ::fingera::unpack(_stream, tmp);
    Setter::set(_object, std::move(tmp));
  }
};
template <typename T>
class if_reflected<
    T, typename std::enable_if<reflector<T>::is_defined::value>::type> {
 public:
  template <typename Stream>
  static inline void pack(Stream &s, const T &value) {
    pack_reflect_visitor<Stream, T> visitor(s, value);
    reflector<T>::visit(visitor);
  }
  template <typename Stream>
  static inline void unpack(Stream &s, T &value) {
    unpack_reflect_visitor<Stream, T> visitor(s, value);
    reflector<T>::visit(visitor);
  }
};
}  // namespace pack_detail

template <typename Stream, typename T>
static inline void pack(Stream &s, const T &value) {
  pack_detail::if_reflected<T>::pack(s, value);
}

template <typename Stream, typename T>
static inline void unpack(Stream &s, T &value) {
  pack_detail::if_reflected<T>::unpack(s, value);
}

}  // namespace fingera