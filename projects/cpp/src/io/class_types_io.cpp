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
#include <stdexcept>
#include "dogen/cpp/io/class_types_io.hpp"

namespace dogen {
namespace cpp {

std::ostream& operator<<(std::ostream& s, const class_types& v) {
    s << "{ " << "\"__type__\": " << "\"class_types\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case class_types::invalid:
        attr = "\"invalid\"";
        break;
    case class_types::user_defined:
        attr = "\"user_defined\"";
        break;
    case class_types::unversioned_key:
        attr = "\"unversioned_key\"";
        break;
    case class_types::versioned_key:
        attr = "\"versioned_key\"";
        break;
    case class_types::service:
        attr = "\"service\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for class_types");
    }
    s << attr << " }";
    return s;
}

} }