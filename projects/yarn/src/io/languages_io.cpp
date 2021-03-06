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
#include <string>
#include <ostream>
#include <stdexcept>
#include "dogen/yarn/io/languages_io.hpp"

namespace dogen {
namespace yarn {

std::ostream& operator<<(std::ostream& s, const languages& v) {
    s << "{ " << "\"__type__\": " << "\"languages\", " << "\"value\": ";

    std::string attr;
    switch (v) {
    case languages::invalid:
        attr = "\"invalid\"";
        break;
    case languages::cpp:
        attr = "\"cpp\"";
        break;
    case languages::csharp:
        attr = "\"csharp\"";
        break;
    case languages::java:
        attr = "\"java\"";
        break;
    case languages::language_agnostic:
        attr = "\"language_agnostic\"";
        break;
    case languages::upsilon:
        attr = "\"upsilon\"";
        break;
    default:
        throw std::invalid_argument("Invalid value for languages");
    }
    s << attr << " }";
    return s;
}

} }
