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

#include <algorithm>
#include <stdexcept>

#include <thrift/compiler/ast/t_structured.h>

namespace apache {
namespace thrift {
namespace compiler {

namespace {

template <typename C>
// Returns a pair<iterator, bool> of (lower bound iterator, id found?).
auto find_by_id(const C& fields_id_order, int32_t id) {
  auto lower = std::partition_point(
      fields_id_order.begin(), fields_id_order.end(), [id](const auto& field) {
        return field->id() < id;
      });
  return std::make_pair(
      lower, lower != fields_id_order.end() && (*lower)->id() == id);
}

} // namespace

bool t_structured::try_append_field(std::unique_ptr<t_field>&& elem) {
  auto existing = find_by_id(fields_id_order_, elem->id());
  if (existing.second) {
    return false;
  }

  // Index the new field.
  if (!fields_.empty()) {
    fields_.back()->set_next(elem.get());
  }

  if (!elem->name().empty()) {
    fields_by_name_.put(*elem);
  }
  fields_ordinal_order_.emplace_back(elem.get());
  fields_id_order_.emplace(existing.first, elem.get());

  fields_raw_.push_back(elem.get());
  fields_raw_id_order_.insert(
      find_by_id(fields_raw_id_order_, elem->id()).first, elem.get());

  // Take ownership.
  fields_.push_back(std::move(elem));
  return true;
}

const t_field* t_structured::get_field_by_id(int32_t id) const {
  auto existing = find_by_id(fields_id_order_, id);
  return existing.second ? *existing.first : nullptr;
}

void t_structured::append(std::unique_ptr<t_field> elem) {
  if (try_append_field(std::move(elem))) {
    return;
  }

  if (elem->get_key() != 0) {
    throw std::runtime_error(
        "Field identifier " + std::to_string(elem->get_key()) + " for \"" +
        elem->get_name() + "\" has already been used");
  }

  // TODO(afuller): Figure out why some code relies on adding multiple id:0
  // fields, fix the code, and remove this hack.
  if (!fields_raw_.empty()) {
    fields_raw_.back()->set_next(elem.get());
  }
  if (!elem->get_name().empty()) {
    fields_by_name_.put(*elem);
  }
  fields_ordinal_order_.push_back(elem.get());
  fields_raw_.push_back(elem.get());
  fields_.push_back(std::move(elem));
}

} // namespace compiler
} // namespace thrift
} // namespace apache
