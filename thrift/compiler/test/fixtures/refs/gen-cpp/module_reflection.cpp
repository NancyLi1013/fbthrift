/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "module_reflection.h"
#include <thrift/lib/cpp/Reflection.h>

 namespace module_reflection_ {

// Reflection initializer for struct module.MyField
void reflectionInitializer_16778989117799402412(::apache::thrift::reflection::Schema& schema) {
  const uint64_t id = 16778989117799402412U;
  if (schema.dataTypes.count(id)) return;
  ::apache::thrift::reflection::DataType& dt = schema.dataTypes[id];
  dt.name = "struct module.MyField";
  schema.names[dt.name] = id;
  dt.__isset.fields = true;
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[1];
    f.isRequired = false;
    f.type = 6U;
    f.name = "opt_value";
    f.order = 0;
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[2];
    f.isRequired = true;
    f.type = 6U;
    f.name = "value";
    f.order = 1;
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[3];
    f.isRequired = true;
    f.type = 6U;
    f.name = "req_value";
    f.order = 2;
  }
}

void  reflectionInitializer_16778989117799402412(::apache::thrift::reflection::Schema&);  // struct module.MyField
// Reflection initializer for struct module.MyStruct
void reflectionInitializer_7958971832214294220(::apache::thrift::reflection::Schema& schema) {
  const uint64_t id = 7958971832214294220U;
  if (schema.dataTypes.count(id)) return;
  ::apache::thrift::reflection::DataType& dt = schema.dataTypes[id];
  dt.name = "struct module.MyStruct";
  schema.names[dt.name] = id;
  dt.__isset.fields = true;
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[1];
    f.isRequired = false;
    f.type = 16778989117799402412U;
    f.name = "opt_ref";
    f.order = 0;
    f.__isset.annotations = true;
    f.annotations["cpp.ref"] = "true";
    f.annotations["cpp2.ref"] = "true";
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[2];
    f.isRequired = true;
    f.type = 16778989117799402412U;
    f.name = "ref";
    f.order = 1;
    f.__isset.annotations = true;
    f.annotations["cpp.ref"] = "true";
    f.annotations["cpp2.ref"] = "true";
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[3];
    f.isRequired = true;
    f.type = 16778989117799402412U;
    f.name = "req_ref";
    f.order = 2;
    f.__isset.annotations = true;
    f.annotations["cpp.ref"] = "true";
    f.annotations["cpp2.ref"] = "true";
  }
  reflectionInitializer_16778989117799402412(schema);  // struct module.MyField
}

// Reflection initializer for struct module.MyUnion
void reflectionInitializer_15877789207728179884(::apache::thrift::reflection::Schema& schema) {
  const uint64_t id = 15877789207728179884U;
  if (schema.dataTypes.count(id)) return;
  ::apache::thrift::reflection::DataType& dt = schema.dataTypes[id];
  dt.name = "struct module.MyUnion";
  schema.names[dt.name] = id;
  dt.__isset.fields = true;
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[1];
    f.isRequired = true;
    f.type = 5U;
    f.name = "anInteger";
    f.order = 0;
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[2];
    f.isRequired = true;
    f.type = 1U;
    f.name = "aString";
    f.order = 1;
  }
}

void  reflectionInitializer_15877789207728179884(::apache::thrift::reflection::Schema&);  // struct module.MyUnion
void  reflectionInitializer_16778989117799402412(::apache::thrift::reflection::Schema&);  // struct module.MyField
// Reflection initializer for struct module.StructWithUnion
void reflectionInitializer_11295191354176986988(::apache::thrift::reflection::Schema& schema) {
  const uint64_t id = 11295191354176986988U;
  if (schema.dataTypes.count(id)) return;
  ::apache::thrift::reflection::DataType& dt = schema.dataTypes[id];
  dt.name = "struct module.StructWithUnion";
  schema.names[dt.name] = id;
  dt.__isset.fields = true;
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[1];
    f.isRequired = true;
    f.type = 15877789207728179884U;
    f.name = "u";
    f.order = 0;
    f.__isset.annotations = true;
    f.annotations["cpp.ref"] = "true";
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[2];
    f.isRequired = true;
    f.type = 7U;
    f.name = "aDouble";
    f.order = 1;
  }
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[3];
    f.isRequired = true;
    f.type = 16778989117799402412U;
    f.name = "f";
    f.order = 2;
  }
  reflectionInitializer_15877789207728179884(schema);  // struct module.MyUnion
  reflectionInitializer_16778989117799402412(schema);  // struct module.MyField
}

void  reflectionInitializer_2826922994162023308(::apache::thrift::reflection::Schema&);  // struct module.RecursiveStruct
// Reflection initializer for list<struct module.RecursiveStruct>
static void reflectionInitializer_1481110219371736233(::apache::thrift::reflection::Schema& schema) {
  const uint64_t id = 1481110219371736233U;
  if (schema.dataTypes.count(id)) return;
  ::apache::thrift::reflection::DataType& dt = schema.dataTypes[id];
  dt.name = "list<struct module.RecursiveStruct>";
  schema.names[dt.name] = id;
  dt.__isset.valueType = true;
  dt.valueType = 2826922994162023308U;
  reflectionInitializer_2826922994162023308(schema);  // struct module.RecursiveStruct
}

static void  reflectionInitializer_1481110219371736233(::apache::thrift::reflection::Schema&);  // list<struct module.RecursiveStruct>
// Reflection initializer for struct module.RecursiveStruct
void reflectionInitializer_2826922994162023308(::apache::thrift::reflection::Schema& schema) {
  const uint64_t id = 2826922994162023308U;
  if (schema.dataTypes.count(id)) return;
  ::apache::thrift::reflection::DataType& dt = schema.dataTypes[id];
  dt.name = "struct module.RecursiveStruct";
  schema.names[dt.name] = id;
  dt.__isset.fields = true;
  {
    ::apache::thrift::reflection::StructField& f = dt.fields[1];
    f.isRequired = false;
    f.type = 1481110219371736233U;
    f.name = "mes";
    f.order = 0;
  }
  reflectionInitializer_1481110219371736233(schema);  // list<struct module.RecursiveStruct>
}

}

