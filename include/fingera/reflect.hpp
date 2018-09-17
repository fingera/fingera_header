/**
 * @brief 可定制的反射 方便 Json 和 Binary 序列化
 *
 * @file reflect.hpp
 * @author liuyujun@fingera.cn
 * @date 2018-09-14
 */
#pragma once

#include <type_traits>

namespace fingera {

template <typename T>
class reflector {
 public:
  using type = T;
  using is_defined = std::false_type;
  using is_enum = std::false_type;
};

template <typename ClassType, typename MemType, MemType(ClassType::*pointer),
          typename ExportType = MemType>
class member_getter_setter {
 public:
  static inline ExportType get(const ClassType &object) {
    return object.*pointer;
  }
  static inline void set(ClassType &object, const ExportType &value) {
    object.*pointer = value;
  }
};

template <typename ClassType, typename ExportType, typename GetterType,
          typename SetterType, GetterType getter, SetterType setter>
class member_func_getter_setter {
 public:
  static inline ExportType get(const ClassType &object) {
    return (object.*getter)();
  }
  static inline void set(ClassType &object, const ExportType &value) {
    (object.*setter)(value);
  }
};

#define FR_MEM_FULL(name, export_type, export_name)                      \
  {                                                                      \
    using mem_type = decltype((static_cast<type *>(nullptr))->name);     \
    v.template visit<                                                    \
        member_getter_setter<type, mem_type, &type::name, export_type>>( \
        #export_name);                                                   \
  }

#define FR_MEM(name) \
  FR_MEM_FULL(name, decltype((static_cast<type *>(nullptr))->name), name)

#define FR_MEM_NAME(name, new_name) \
  FR_MEM_FULL(name, decltype((static_cast<type *>(nullptr))->name), new_name)

#define FR_MEM_TYPE(name, export_type) FR_MEM_FULL(name, export_type, name)

#define FR_MEM_FUNC(name, export_type, getter, setter)                       \
  {                                                                          \
    v.template visit<member_func_getter_setter<                              \
        type, export_type, decltype(&type::getter), decltype(&type::setter), \
        &type::getter, &type::setter>>(#name);                               \
  }

#define FR_SUPER(base) fingera::reflector<base>::visit<Visitor>(v);

#define FINGERA_REFLECT(T, ...)        \
  namespace fingera {                  \
  template <>                          \
  class reflector<T> {                 \
   public:                             \
    using type = T;                    \
    using is_defined = std::true_type; \
    using is_enum = std::false_type;   \
    template <typename Visitor>        \
    static void visit(Visitor &v) {    \
      __VA_ARGS__                      \
    }                                  \
  };                                   \
  }

}  // namespace fingera
