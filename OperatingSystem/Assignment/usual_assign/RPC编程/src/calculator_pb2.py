# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: calculator.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import builder as _builder
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x10\x63\x61lculator.proto\x12\ncalculator\"5\n\x0fMultiplyRequest\x12\x10\n\x08operand1\x18\x01 \x01(\x05\x12\x10\n\x08operand2\x18\x02 \x01(\x05\"\"\n\x10MultiplyResponse\x12\x0e\n\x06result\x18\x01 \x01(\x05\x32U\n\nCalculator\x12G\n\x08Multiply\x12\x1b.calculator.MultiplyRequest\x1a\x1c.calculator.MultiplyResponse\"\x00\x62\x06proto3')

_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, globals())
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'calculator_pb2', globals())
if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _MULTIPLYREQUEST._serialized_start=32
  _MULTIPLYREQUEST._serialized_end=85
  _MULTIPLYRESPONSE._serialized_start=87
  _MULTIPLYRESPONSE._serialized_end=121
  _CALCULATOR._serialized_start=123
  _CALCULATOR._serialized_end=208
# @@protoc_insertion_point(module_scope)
