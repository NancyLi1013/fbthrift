/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <thrift/compiler/ast/t_struct.h>

namespace apache {
namespace thrift {
namespace compiler {

class t_program;

/**
 * The exceptions thrown by a t_function, t_sink, etc.
 */
// TODO(afuller): Inherit from t_structured instead.
class t_throws : public t_struct {
 public:
  t_throws() : t_struct(nullptr, "") {}

  static const t_throws* no_exceptions() {
    static const auto* kEmpty = new t_throws;
    return kEmpty;
  }

  // A helper that returns `no_exceptions` if value == nullptr.
  static const t_throws* or_empty(const t_throws* value) {
    return value == nullptr ? no_exceptions() : value;
  }

 private:
  friend class t_structured;
  t_throws* clone_DO_NOT_USE() const override {
    auto clone = std::make_unique<t_throws>();
    clone_structured(clone.get());
    return clone.release();
  }
};

} // namespace compiler
} // namespace thrift
} // namespace apache
