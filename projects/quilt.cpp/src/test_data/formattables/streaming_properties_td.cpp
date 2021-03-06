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
#include <sstream>
#include "dogen/quilt.cpp/test_data/formattables/streaming_properties_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

std::string create_std_string(const unsigned int position) {
    std::ostringstream s;
    s << "a_string_" << position;
    return s.str();
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

streaming_properties_generator::streaming_properties_generator() : position_(0) { }

void streaming_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.requires_quoting(create_bool(position + 0));
    v.string_conversion_method(create_std_string(position + 1));
    v.remove_unprintable_characters(create_bool(position + 2));
}

streaming_properties_generator::result_type
streaming_properties_generator::create(const unsigned int position) {
    streaming_properties r;
    streaming_properties_generator::populate(position, r);
    return r;
}

streaming_properties_generator::result_type*
streaming_properties_generator::create_ptr(const unsigned int position) {
    streaming_properties* p = new streaming_properties();
    streaming_properties_generator::populate(position, *p);
    return p;
}

streaming_properties_generator::result_type
streaming_properties_generator::operator()() {
    return create(position_++);
}

} } } }
