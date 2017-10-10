#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#

from libcpp.memory cimport shared_ptr, make_shared, unique_ptr, make_unique
from libcpp.string cimport string
from libcpp cimport bool as cbool
from libcpp.iterator cimport inserter as cinserter
from cpython cimport bool as pbool
from libc.stdint cimport int8_t, int16_t, int32_t, int64_t, uint32_t
from cython.operator cimport dereference as deref, preincrement as inc
import thrift.py3.types
cimport thrift.py3.types
cimport thrift.py3.exceptions
from thrift.py3.types import NOTSET
from thrift.py3.types cimport translate_cpp_enum_to_python
cimport thrift.py3.std_libcpp as std_libcpp
from thrift.py3.serializer cimport IOBuf
from thrift.py3.serializer import Protocol
cimport thrift.py3.serializer as serializer
from thrift.py3.serializer import deserialize, serialize

import sys
from collections.abc import Sequence, Set, Mapping, Iterable
from enum import Enum
import warnings
cimport transitive.types
import transitive.types




cdef cIncluded _Included_defaults = cIncluded()

cdef class Included(thrift.py3.types.Struct):

    def __init__(
        Included self,
        MyIntField=None,
        MyTransitiveField=None
    ):
        self._cpp_obj = move(Included._make_instance(
          NULL,
          MyIntField,
          MyTransitiveField,
        ))

    def __call__(
        Included self,
        MyIntField=NOTSET,
        MyTransitiveField=NOTSET
    ):
        changes = any((
            MyIntField is not NOTSET,

            MyTransitiveField is not NOTSET,
        ))

        if not changes:
            return self

        inst = <Included>Included.__new__(Included)
        inst._cpp_obj = move(Included._make_instance(
          self._cpp_obj.get(),
          MyIntField,
          MyTransitiveField,
        ))
        return inst

    @staticmethod
    cdef unique_ptr[cIncluded] _make_instance(
        cIncluded* base_instance,
        object MyIntField,
        object MyTransitiveField
    ) except *:
        cdef unique_ptr[cIncluded] c_inst
        if base_instance:
            c_inst = make_unique[cIncluded](deref(base_instance))
        else:
            c_inst = make_unique[cIncluded]()

        if base_instance:
            # Convert None's to default value.
            if MyIntField is None:
                deref(c_inst).MyIntField = _Included_defaults.MyIntField
                deref(c_inst).__isset.MyIntField = False
            elif MyIntField is NOTSET:
                MyIntField = None

            if MyTransitiveField is None:
                deref(c_inst).MyTransitiveField = _Included_defaults.MyTransitiveField
                deref(c_inst).__isset.MyTransitiveField = False
            elif MyTransitiveField is NOTSET:
                MyTransitiveField = None

        if MyIntField is not None:
            deref(c_inst).MyIntField = MyIntField
            deref(c_inst).__isset.MyIntField = True

        if MyTransitiveField is not None:
            deref(c_inst).MyTransitiveField = deref((<transitive.types.Foo?> MyTransitiveField)._cpp_obj)
            deref(c_inst).__isset.MyTransitiveField = True

        # in C++ you don't have to call move(), but this doesn't translate
        # into a C++ return statement, so you do here
        return move_unique(c_inst)

    def __iter__(self):
        yield 'MyIntField', self.MyIntField
        yield 'MyTransitiveField', self.MyTransitiveField

    def __bool__(self):
        return deref(self._cpp_obj).__isset.MyIntField or deref(self._cpp_obj).__isset.MyTransitiveField

    @staticmethod
    cdef create(shared_ptr[cIncluded] cpp_obj):
        inst = <Included>Included.__new__(Included)
        inst._cpp_obj = cpp_obj
        return inst

    @property
    def MyIntField(self):
        return self._cpp_obj.get().MyIntField

    @property
    def MyTransitiveField(self):
        if self.__MyTransitiveField is None:
            self.__MyTransitiveField = transitive.types.Foo.create(make_shared[transitive.types.cFoo](deref(self._cpp_obj).MyTransitiveField))
        return self.__MyTransitiveField


    def __hash__(Included self):
        if not self.__hash:
            self.__hash = hash((
            self.MyIntField,
            self.MyTransitiveField,
            ))
        return self.__hash

    def __repr__(Included self):
        return f'Included(MyIntField={repr(self.MyIntField)}, MyTransitiveField={repr(self.MyTransitiveField)})'
    def __richcmp__(self, other, op):
        cdef int cop = op
        if cop not in (2, 3):
            raise TypeError("unorderable types: {}, {}".format(self, other))
        if not (
                isinstance(self, Included) and
                isinstance(other, Included)):
            if cop == 2:  # different types are never equal
                return False
            else:         # different types are always notequal
                return True

        cdef cIncluded cself = deref((<Included>self)._cpp_obj)
        cdef cIncluded cother = deref((<Included>other)._cpp_obj)
        cdef cbool cmp = cself == cother
        if cop == 2:
            return cmp
        return not cmp

    cdef bytes _serialize(Included self, proto):
        cdef string c_str
        if proto is Protocol.COMPACT:
            serializer.CompactSerialize[cIncluded](deref(self._cpp_obj.get()), &c_str)
        elif proto is Protocol.BINARY:
            serializer.BinarySerialize[cIncluded](deref(self._cpp_obj.get()), &c_str)
        elif proto is Protocol.JSON:
            serializer.JSONSerialize[cIncluded](deref(self._cpp_obj.get()), &c_str)
        return <bytes> c_str

    cdef uint32_t _deserialize(Included self, const IOBuf* buf, proto):
        cdef uint32_t needed
        if proto is Protocol.COMPACT:
            needed = serializer.CompactDeserialize[cIncluded](buf, deref(self._cpp_obj.get()))
        elif proto is Protocol.BINARY:
            needed = serializer.BinaryDeserialize[cIncluded](buf, deref(self._cpp_obj.get()))
        elif proto is Protocol.JSON:
            needed = serializer.JSONDeserialize[cIncluded](buf, deref(self._cpp_obj.get()))
        return needed

    def __reduce__(self):
        return (deserialize, (Included, serialize(self)))


ExampleIncluded = Included.create(make_shared[cIncluded](cExampleIncluded()))
IncludedConstant = 42
IncludedInt64 = int
