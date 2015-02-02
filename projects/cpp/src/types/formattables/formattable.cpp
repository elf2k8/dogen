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
#include "dogen/cpp/types/formattables/formattable.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

formattable::formattable(const std::string& identity)
    : identity_(identity) { }

void formattable::swap(formattable& other) noexcept {
    using std::swap;
    swap(identity_, other.identity_);
}

bool formattable::operator==(const formattable& rhs) const {
    return identity_ == rhs.identity_;
}

formattable& formattable::operator=(formattable other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

const std::string& formattable::identity() const {
    return identity_;
}

std::string& formattable::identity() {
    return identity_;
}

void formattable::identity(const std::string& v) {
    identity_ = v;
}

void formattable::identity(const std::string&& v) {
    identity_ = std::move(v);
}

} } }