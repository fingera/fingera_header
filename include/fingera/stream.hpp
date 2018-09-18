/**
 * @brief 实现基础的Stream
 *
 * @file stream.hpp
 * @author liuyujun@fingera.cn
 * @date 2018-09-18
 */
#pragma once

#include <cstdint>
#include <cstring>

#include <stdexcept>
#include <vector>

namespace fingera {

class write_stream {
 protected:
  std::vector<uint8_t> _data;

 public:
  write_stream() {}
  ~write_stream() {}

  inline void write(const void *data, size_t size) {
    const uint8_t *ptr = reinterpret_cast<const uint8_t *>(data);
    _data.insert(_data.end(), ptr, ptr + size);
  }

  inline std::vector<uint8_t> &data() { return _data; }
};

class read_stream {
 protected:
  const std::vector<uint8_t> &_data;
  size_t _cursor;

 public:
  read_stream(const std::vector<uint8_t> &data) : _data(data), _cursor(0) {}
  ~read_stream() {}

  inline void read(void *buf, size_t size) {
    if (_cursor + size > _data.size()) {
      throw std::overflow_error("read_stream::read");
    }
    memcpy(buf, &_data[_cursor], size);
    _cursor += size;
  }

  inline bool valid() { return _cursor < _data.size(); }
};

}  // namespace fingera