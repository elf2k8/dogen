/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/quilt.cpp/types/formattables/inclusion_directive_configuration.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

inclusion_directive_configuration::inclusion_directive_configuration()
    : inclusion_required_(static_cast<bool>(0)) { }

inclusion_directive_configuration::inclusion_directive_configuration(
    const bool inclusion_required,
    const std::string& inclusion_directive)
    : inclusion_required_(inclusion_required),
      inclusion_directive_(inclusion_directive) { }

void inclusion_directive_configuration::swap(inclusion_directive_configuration& other) noexcept {
    using std::swap;
    swap(inclusion_required_, other.inclusion_required_);
    swap(inclusion_directive_, other.inclusion_directive_);
}

bool inclusion_directive_configuration::operator==(const inclusion_directive_configuration& rhs) const {
    return inclusion_required_ == rhs.inclusion_required_ &&
        inclusion_directive_ == rhs.inclusion_directive_;
}

inclusion_directive_configuration& inclusion_directive_configuration::operator=(inclusion_directive_configuration other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool inclusion_directive_configuration::inclusion_required() const {
    return inclusion_required_;
}

void inclusion_directive_configuration::inclusion_required(const bool v) {
    inclusion_required_ = v;
}

const std::string& inclusion_directive_configuration::inclusion_directive() const {
    return inclusion_directive_;
}

std::string& inclusion_directive_configuration::inclusion_directive() {
    return inclusion_directive_;
}

void inclusion_directive_configuration::inclusion_directive(const std::string& v) {
    inclusion_directive_ = v;
}

void inclusion_directive_configuration::inclusion_directive(const std::string&& v) {
    inclusion_directive_ = std::move(v);
}

} } } }
