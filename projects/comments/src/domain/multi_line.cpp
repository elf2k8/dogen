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
#include "dogen/comments/domain/multi_line.hpp"

namespace dogen {
namespace comments {

multi_line::multi_line(const dogen::comments::versioned_key& versioned_key)
    : versioned_key_(versioned_key) { }

void multi_line::swap(multi_line& other) noexcept {
    using std::swap;
    swap(versioned_key_, other.versioned_key_);
}

bool multi_line::operator==(const multi_line& rhs) const {
    return versioned_key_ == rhs.versioned_key_;
}

multi_line& multi_line::operator=(multi_line other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

} }