
#include <fingera/pack.hpp>
#include <fingera/reflect.hpp>
#include <fingera/stream.hpp>

#include <string>

#include <stdio.h>

#include <gtest/gtest.h>

class test_class_base {
  int _age;

 public:
  std::string name;

  test_class_base() : _age(100), name("test_class_base") {}
  test_class_base(const std::string& n, int age) : _age(age), name(n) {}

  int get_age() const { return _age; }
  void set_age(int age) { _age = age; }
};

FINGERA_REFLECT_BEGIN(test_class_base)
FR_MEMBER_FUNC(age, int32_t, get_age, set_age)
FR_MEMBER_BASE(name)
FINGERA_REFLECT_END()

class test_class_child : public test_class_base {
  int _height;

 public:
  int weight;
  std::string tag;
  std::string ddddd;
  test_class_child() : _height(20), weight(30), tag("TAG"), ddddd("Hello") {}
  test_class_child(const std::string& n, int age)
      : test_class_base(n, age), _height(0), weight(0), tag(""), ddddd("") {}

  int get_height() const { return _height; }
  void set_height(int height) { _height = height; }
};

FINGERA_REFLECT_BEGIN(test_class_child)
FR_SUPER_CLASS(test_class_base)
FR_MEMBER_FUNC(height, int16_t, get_height, set_height)
FR_MEMBER_TYPE(weight, int32_t)
FR_MEMBER_BASE(tag)
FR_MEMBER_NAME(ddddd, say_hello)
FINGERA_REFLECT_END()

class extra_write_stream : public fingera::write_stream {};
class extra_read_stream : public fingera::read_stream {
 public:
  extra_read_stream(const std::vector<uint8_t>& data)
      : fingera::read_stream(data) {}
};

extra_write_stream& operator<<(extra_write_stream& s,
                               const std::string& value) {
  uint32_t size = (uint32_t)value.size();
  s.write(&size, sizeof(size));
  s.write(value.c_str(), size);
  return s;
}
inline extra_read_stream& operator>>(extra_read_stream& s, std::string& value) {
  uint32_t size;
  s.read(&size, sizeof(size));
  value.resize(size);
  s.read((char*)value.c_str(), value.size());
  return s;
}

template <typename T>
void test_object(const T& obj, const char* buffer, size_t size) {
  extra_write_stream stream;
  std::vector<uint8_t> copy_buffer(buffer, buffer + size);
  extra_read_stream reader(copy_buffer);
  fingera::pack(stream, obj);
  EXPECT_EQ(stream.data().size(), size);
  EXPECT_FALSE(memcmp(buffer, stream.data().data(), size));
  T newObject("NONONO", 0);
  fingera::unpack(reader, newObject);
  EXPECT_EQ(newObject.get_age(), obj.get_age());
  EXPECT_EQ(newObject.name, obj.name);
  EXPECT_FALSE(reader.valid());
  try {
    fingera::unpack(reader, newObject);
    EXPECT_FALSE(true);
  } catch (std::overflow_error& ex) {
    _unused_(ex);
  }
}

TEST(fingera_reflect, all) {
  const char base_buffer[] = {
      100, 0,  0,   0,  15,  0,   0,  0,  116, 101, 115, 116,
      95,  99, 108, 97, 115, 115, 95, 98, 97,  115, 101,
  };
  const char child_buffer[] = {
      100, 0,   0,   0,  15, 0,  0,   0,   116, 101, 115, 116, 95,  99,  108,
      97,  115, 115, 95, 98, 97, 115, 101, 20,  0,   30,  0,   0,   0,   3,
      0,   0,   0,   84, 65, 71, 5,   0,   0,   0,   72,  101, 108, 108, 111,
  };
  test_object(test_class_base(), base_buffer, sizeof(base_buffer));
  test_object(test_class_child(), child_buffer, sizeof(child_buffer));
}
