#include <fingera/reflect.hpp>

#include <stdio.h>

#include <gtest/gtest.h>

class test_class_base {
  int _age;

 public:
  std::string name;

  test_class_base() : _age(100), name("test_class_base") {}

  int get_age() const { return _age; }
  void set_age(int age) { _age = age; }
};

FINGERA_REFLECT(test_class_base,
                FR_MEM_FUNC(age, int32_t, get_age, set_age) FR_MEM(name));

class test_class_child : public test_class_base {
  int _height;

 public:
  int weight;
  std::string tag;
  test_class_child() : _height(20), weight(30), tag("TAG") {}

  int get_height() const { return _height; }
  void set_height(int height) { _height = height; }
};

FINGERA_REFLECT(test_class_child,
                FR_SUPER(test_class_base)
                    FR_MEM_FUNC(height, int16_t, get_height, set_height)
                        FR_MEM_TYPE(weight, int32_t) FR_MEM(tag));

template <typename T>
struct DumpVisitor {
  const T &_obj;
  DumpVisitor(const T &obj) : _obj(obj) {}
  template <typename Getter>
  void visit(const char *name) {
    std::cout << name << ":" << Getter::get(_obj);
    std::cout << std::endl;
  }

  static void dump(const T &obj) {
    DumpVisitor<T> dump(obj);
    fingera::reflector<T>::visit(dump);
  }
};

TEST(fingera_reflect, all) {
  DumpVisitor<test_class_child>::dump(test_class_child());
}
