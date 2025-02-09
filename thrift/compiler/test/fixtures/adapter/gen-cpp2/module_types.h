/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/module_types_h.h>



namespace apache {
namespace thrift {
namespace tag {
struct intField;
struct optionalIntField;
struct intFieldWithDefault;
struct setField;
struct optionalSetField;
struct mapField;
struct optionalMapField;
struct structField;
struct optionalStructField;
struct structListField;
struct optionalStructListField;
} // namespace tag
namespace detail {
#ifndef APACHE_THRIFT_ACCESSOR_intField
#define APACHE_THRIFT_ACCESSOR_intField
APACHE_THRIFT_DEFINE_ACCESSOR(intField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_optionalIntField
#define APACHE_THRIFT_ACCESSOR_optionalIntField
APACHE_THRIFT_DEFINE_ACCESSOR(optionalIntField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_intFieldWithDefault
#define APACHE_THRIFT_ACCESSOR_intFieldWithDefault
APACHE_THRIFT_DEFINE_ACCESSOR(intFieldWithDefault);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_setField
#define APACHE_THRIFT_ACCESSOR_setField
APACHE_THRIFT_DEFINE_ACCESSOR(setField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_optionalSetField
#define APACHE_THRIFT_ACCESSOR_optionalSetField
APACHE_THRIFT_DEFINE_ACCESSOR(optionalSetField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_mapField
#define APACHE_THRIFT_ACCESSOR_mapField
APACHE_THRIFT_DEFINE_ACCESSOR(mapField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_optionalMapField
#define APACHE_THRIFT_ACCESSOR_optionalMapField
APACHE_THRIFT_DEFINE_ACCESSOR(optionalMapField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_structField
#define APACHE_THRIFT_ACCESSOR_structField
APACHE_THRIFT_DEFINE_ACCESSOR(structField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_optionalStructField
#define APACHE_THRIFT_ACCESSOR_optionalStructField
APACHE_THRIFT_DEFINE_ACCESSOR(optionalStructField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_structListField
#define APACHE_THRIFT_ACCESSOR_structListField
APACHE_THRIFT_DEFINE_ACCESSOR(structListField);
#endif
#ifndef APACHE_THRIFT_ACCESSOR_optionalStructListField
#define APACHE_THRIFT_ACCESSOR_optionalStructListField
APACHE_THRIFT_DEFINE_ACCESSOR(optionalStructListField);
#endif
} // namespace detail
} // namespace thrift
} // namespace apache

// BEGIN declare_enums

// END declare_enums
// BEGIN forward_declare
namespace cpp2 {
class Foo;
class Bar;
} // cpp2
// END forward_declare
// BEGIN typedefs
namespace cpp2 {
typedef ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::std::set<::std::string>> SetWithAdapter;
typedef ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::string>> ListWithElemAdapter;
typedef ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::Bar> StructWithAdapter;

} // cpp2
// END typedefs
// BEGIN hash_and_equal_to
// END hash_and_equal_to
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
namespace cpp2 {
#ifndef SWIG
using ::apache::thrift::detail::operator!=;
using ::apache::thrift::detail::operator>;
using ::apache::thrift::detail::operator<=;
using ::apache::thrift::detail::operator>=;
#endif

class Foo final  {
 private:
  friend struct ::apache::thrift::detail::st::struct_private_access;

  //  used by a static_assert in the corresponding source
  static constexpr bool __fbthrift_cpp2_gen_json = false;
  static constexpr bool __fbthrift_cpp2_gen_nimble = false;
  static constexpr bool __fbthrift_cpp2_gen_has_thrift_uri = false;

 public:
  using __fbthrift_cpp2_type = Foo;
  static constexpr bool __fbthrift_cpp2_is_union =
    false;


 public:

  Foo();

  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  Foo(apache::thrift::FragileConstructor, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> optionalIntField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intFieldWithDefault__arg, ::cpp2::SetWithAdapter setField__arg, ::cpp2::SetWithAdapter optionalSetField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> mapField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> optionalMapField__arg);

  Foo(Foo&&) noexcept;

  Foo(const Foo& src);


  Foo& operator=(Foo&&) noexcept;
  Foo& operator=(const Foo& src);
  void __clear();

  ~Foo();

 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intField;
 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> optionalIntField;
 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intFieldWithDefault;
 private:
  ::cpp2::SetWithAdapter setField;
 private:
  ::cpp2::SetWithAdapter optionalSetField;
 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> mapField;
 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> optionalMapField;

 public:
  [[deprecated("__isset field is deprecated in Thrift struct. Use _ref() accessors instead.")]]
  struct __isset {
    bool intField;
    bool optionalIntField;
    bool intFieldWithDefault;
    bool setField;
    bool optionalSetField;
    bool mapField;
    bool optionalMapField;
  } __isset = {};

 public:

  bool operator==(const Foo&) const;
  bool operator<(const Foo&) const;

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> intField_ref() const& {
    return {this->intField, __isset.intField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> intField_ref() const&& {
    return {std::move(this->intField), __isset.intField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> intField_ref() & {
    return {this->intField, __isset.intField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> intField_ref() && {
    return {std::move(this->intField), __isset.intField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&> optionalIntField_ref() const& {
    return {this->optionalIntField, __isset.optionalIntField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&&> optionalIntField_ref() const&& {
    return {std::move(this->optionalIntField), __isset.optionalIntField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&> optionalIntField_ref() & {
    return {this->optionalIntField, __isset.optionalIntField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&&> optionalIntField_ref() && {
    return {std::move(this->optionalIntField), __isset.optionalIntField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> intFieldWithDefault_ref() const& {
    return {this->intFieldWithDefault, __isset.intFieldWithDefault};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> intFieldWithDefault_ref() const&& {
    return {std::move(this->intFieldWithDefault), __isset.intFieldWithDefault};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> intFieldWithDefault_ref() & {
    return {this->intFieldWithDefault, __isset.intFieldWithDefault};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> intFieldWithDefault_ref() && {
    return {std::move(this->intFieldWithDefault), __isset.intFieldWithDefault};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> setField_ref() const& {
    return {this->setField, __isset.setField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> setField_ref() const&& {
    return {std::move(this->setField), __isset.setField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> setField_ref() & {
    return {this->setField, __isset.setField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> setField_ref() && {
    return {std::move(this->setField), __isset.setField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&> optionalSetField_ref() const& {
    return {this->optionalSetField, __isset.optionalSetField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&&> optionalSetField_ref() const&& {
    return {std::move(this->optionalSetField), __isset.optionalSetField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&> optionalSetField_ref() & {
    return {this->optionalSetField, __isset.optionalSetField};
  }

  template <typename..., typename T = ::cpp2::SetWithAdapter>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&&> optionalSetField_ref() && {
    return {std::move(this->optionalSetField), __isset.optionalSetField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> mapField_ref() const& {
    return {this->mapField, __isset.mapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> mapField_ref() const&& {
    return {std::move(this->mapField), __isset.mapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> mapField_ref() & {
    return {this->mapField, __isset.mapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> mapField_ref() && {
    return {std::move(this->mapField), __isset.mapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&> optionalMapField_ref() const& {
    return {this->optionalMapField, __isset.optionalMapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&&> optionalMapField_ref() const&& {
    return {std::move(this->optionalMapField), __isset.optionalMapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&> optionalMapField_ref() & {
    return {this->optionalMapField, __isset.optionalMapField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&&> optionalMapField_ref() && {
    return {std::move(this->optionalMapField), __isset.optionalMapField};
  }

  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> get_intField() const {
    return intField;
  }

  [[deprecated("Use `FOO.intField_ref() = BAR;` instead of `FOO.set_intField(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>& set_intField(::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intField_) {
    intField = intField_;
    __isset.intField = true;
    return intField;
  }

  const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>* get_optionalIntField() const& {
    return optionalIntField_ref() ? std::addressof(optionalIntField) : nullptr;
  }

  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>* get_optionalIntField() & {
    return optionalIntField_ref() ? std::addressof(optionalIntField) : nullptr;
  }
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>* get_optionalIntField() && = delete;

  [[deprecated("Use `FOO.optionalIntField_ref() = BAR;` instead of `FOO.set_optionalIntField(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>& set_optionalIntField(::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> optionalIntField_) {
    optionalIntField = optionalIntField_;
    __isset.optionalIntField = true;
    return optionalIntField;
  }

  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> get_intFieldWithDefault() const {
    return intFieldWithDefault;
  }

  [[deprecated("Use `FOO.intFieldWithDefault_ref() = BAR;` instead of `FOO.set_intFieldWithDefault(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t>& set_intFieldWithDefault(::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intFieldWithDefault_) {
    intFieldWithDefault = intFieldWithDefault_;
    __isset.intFieldWithDefault = true;
    return intFieldWithDefault;
  }
  const ::cpp2::SetWithAdapter& get_setField() const&;
  ::cpp2::SetWithAdapter get_setField() &&;

  template <typename T_Foo_setField_struct_setter = ::cpp2::SetWithAdapter>
  [[deprecated("Use `FOO.setField_ref() = BAR;` instead of `FOO.set_setField(BAR);`")]]
  ::cpp2::SetWithAdapter& set_setField(T_Foo_setField_struct_setter&& setField_) {
    setField = std::forward<T_Foo_setField_struct_setter>(setField_);
    __isset.setField = true;
    return setField;
  }
  const ::cpp2::SetWithAdapter* get_optionalSetField() const&;
  ::cpp2::SetWithAdapter* get_optionalSetField() &;
  ::cpp2::SetWithAdapter* get_optionalSetField() && = delete;

  template <typename T_Foo_optionalSetField_struct_setter = ::cpp2::SetWithAdapter>
  [[deprecated("Use `FOO.optionalSetField_ref() = BAR;` instead of `FOO.set_optionalSetField(BAR);`")]]
  ::cpp2::SetWithAdapter& set_optionalSetField(T_Foo_optionalSetField_struct_setter&& optionalSetField_) {
    optionalSetField = std::forward<T_Foo_optionalSetField_struct_setter>(optionalSetField_);
    __isset.optionalSetField = true;
    return optionalSetField;
  }
  const ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>& get_mapField() const&;
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> get_mapField() &&;

  template <typename T_Foo_mapField_struct_setter = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  [[deprecated("Use `FOO.mapField_ref() = BAR;` instead of `FOO.set_mapField(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>& set_mapField(T_Foo_mapField_struct_setter&& mapField_) {
    mapField = std::forward<T_Foo_mapField_struct_setter>(mapField_);
    __isset.mapField = true;
    return mapField;
  }
  const ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>* get_optionalMapField() const&;
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>* get_optionalMapField() &;
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>* get_optionalMapField() && = delete;

  template <typename T_Foo_optionalMapField_struct_setter = ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>>
  [[deprecated("Use `FOO.optionalMapField_ref() = BAR;` instead of `FOO.set_optionalMapField(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>& set_optionalMapField(T_Foo_optionalMapField_struct_setter&& optionalMapField_) {
    optionalMapField = std::forward<T_Foo_optionalMapField_struct_setter>(optionalMapField_);
    __isset.optionalMapField = true;
    return optionalMapField;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  template <class Protocol_>
  void readNoXfer(Protocol_* iprot);

  friend class ::apache::thrift::Cpp2Ops<Foo>;
  friend void swap(Foo& a, Foo& b);
};

template <class Protocol_>
uint32_t Foo::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

} // cpp2
namespace cpp2 {
#ifndef SWIG
using ::apache::thrift::detail::operator!=;
using ::apache::thrift::detail::operator>;
using ::apache::thrift::detail::operator<=;
using ::apache::thrift::detail::operator>=;
#endif

class Bar final  {
 private:
  friend struct ::apache::thrift::detail::st::struct_private_access;

  //  used by a static_assert in the corresponding source
  static constexpr bool __fbthrift_cpp2_gen_json = false;
  static constexpr bool __fbthrift_cpp2_gen_nimble = false;
  static constexpr bool __fbthrift_cpp2_gen_has_thrift_uri = false;

 public:
  using __fbthrift_cpp2_type = Bar;
  static constexpr bool __fbthrift_cpp2_is_union =
    false;


 public:

  Bar() {
  }
  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  Bar(apache::thrift::FragileConstructor, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> structField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> optionalStructField__arg, ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> structListField__arg, ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> optionalStructListField__arg);

  Bar(Bar&&) noexcept;

  Bar(const Bar& src);


  Bar& operator=(Bar&&) noexcept;
  Bar& operator=(const Bar& src);
  void __clear();
 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> structField;
 private:
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> optionalStructField;
 private:
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> structListField;
 private:
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> optionalStructListField;

 public:
  [[deprecated("__isset field is deprecated in Thrift struct. Use _ref() accessors instead.")]]
  struct __isset {
    bool structField;
    bool optionalStructField;
    bool structListField;
    bool optionalStructListField;
  } __isset = {};

 public:

  bool operator==(const Bar&) const;
  bool operator<(const Bar&) const;

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> structField_ref() const& {
    return {this->structField, __isset.structField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> structField_ref() const&& {
    return {std::move(this->structField), __isset.structField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> structField_ref() & {
    return {this->structField, __isset.structField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> structField_ref() && {
    return {std::move(this->structField), __isset.structField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&> optionalStructField_ref() const& {
    return {this->optionalStructField, __isset.optionalStructField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&&> optionalStructField_ref() const&& {
    return {std::move(this->optionalStructField), __isset.optionalStructField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&> optionalStructField_ref() & {
    return {this->optionalStructField, __isset.optionalStructField};
  }

  template <typename..., typename T = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&&> optionalStructField_ref() && {
    return {std::move(this->optionalStructField), __isset.optionalStructField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&> structListField_ref() const& {
    return {this->structListField, __isset.structListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::field_ref<const T&&> structListField_ref() const&& {
    return {std::move(this->structListField), __isset.structListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&> structListField_ref() & {
    return {this->structListField, __isset.structListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::field_ref<T&&> structListField_ref() && {
    return {std::move(this->structListField), __isset.structListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&> optionalStructListField_ref() const& {
    return {this->optionalStructListField, __isset.optionalStructListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<const T&&> optionalStructListField_ref() const&& {
    return {std::move(this->optionalStructListField), __isset.optionalStructListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&> optionalStructListField_ref() & {
    return {this->optionalStructListField, __isset.optionalStructListField};
  }

  template <typename..., typename T = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  FOLLY_ERASE ::apache::thrift::optional_field_ref<T&&> optionalStructListField_ref() && {
    return {std::move(this->optionalStructListField), __isset.optionalStructListField};
  }
  const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>& get_structField() const&;
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> get_structField() &&;

  template <typename T_Bar_structField_struct_setter = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  [[deprecated("Use `FOO.structField_ref() = BAR;` instead of `FOO.set_structField(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>& set_structField(T_Bar_structField_struct_setter&& structField_) {
    structField = std::forward<T_Bar_structField_struct_setter>(structField_);
    __isset.structField = true;
    return structField;
  }
  const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>* get_optionalStructField() const&;
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>* get_optionalStructField() &;
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>* get_optionalStructField() && = delete;

  template <typename T_Bar_optionalStructField_struct_setter = ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>
  [[deprecated("Use `FOO.optionalStructField_ref() = BAR;` instead of `FOO.set_optionalStructField(BAR);`")]]
  ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>& set_optionalStructField(T_Bar_optionalStructField_struct_setter&& optionalStructField_) {
    optionalStructField = std::forward<T_Bar_optionalStructField_struct_setter>(optionalStructField_);
    __isset.optionalStructField = true;
    return optionalStructField;
  }
  const ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>& get_structListField() const&;
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> get_structListField() &&;

  template <typename T_Bar_structListField_struct_setter = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  [[deprecated("Use `FOO.structListField_ref() = BAR;` instead of `FOO.set_structListField(BAR);`")]]
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>& set_structListField(T_Bar_structListField_struct_setter&& structListField_) {
    structListField = std::forward<T_Bar_structListField_struct_setter>(structListField_);
    __isset.structListField = true;
    return structListField;
  }
  const ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>* get_optionalStructListField() const&;
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>* get_optionalStructListField() &;
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>* get_optionalStructListField() && = delete;

  template <typename T_Bar_optionalStructListField_struct_setter = ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>>
  [[deprecated("Use `FOO.optionalStructListField_ref() = BAR;` instead of `FOO.set_optionalStructListField(BAR);`")]]
  ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>& set_optionalStructListField(T_Bar_optionalStructListField_struct_setter&& optionalStructListField_) {
    optionalStructListField = std::forward<T_Bar_optionalStructListField_struct_setter>(optionalStructListField_);
    __isset.optionalStructListField = true;
    return optionalStructListField;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  template <class Protocol_>
  void readNoXfer(Protocol_* iprot);

  friend class ::apache::thrift::Cpp2Ops<Bar>;
  friend void swap(Bar& a, Bar& b);
};

template <class Protocol_>
uint32_t Bar::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

} // cpp2
THRIFT_IGNORE_ISSET_USE_WARNING_END
