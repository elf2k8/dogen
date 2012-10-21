/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <ostream>
#include "dogen/trivial_inheritance/domain/second_child_without_members.hpp"
#include "dogen/trivial_inheritance/io/versioned_key_io.hpp"

namespace dogen {
namespace trivial_inheritance {

second_child_without_members::second_child_without_members(
    const int prop_0,
    const dogen::trivial_inheritance::versioned_key& versioned_key)
    : parent_with_members(prop_0,
      versioned_key) { }

void second_child_without_members::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"second_child_without_members\"" << ", "
      << "\"__parent_0__\": ";
    parent_with_members::to_stream(s);
    s << " }";
}

void second_child_without_members::swap(second_child_without_members& other) noexcept {
    parent_with_members::swap(other);

}

bool second_child_without_members::operator==(const second_child_without_members& rhs) const {
    return parent_with_members::operator==(rhs);
}

second_child_without_members& second_child_without_members::operator=(second_child_without_members other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }