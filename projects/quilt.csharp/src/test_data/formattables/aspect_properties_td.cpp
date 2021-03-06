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
#include "dogen/quilt.csharp/test_data/formattables/aspect_properties_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace quilt {
namespace csharp {
namespace formattables {

aspect_properties_generator::aspect_properties_generator() : position_(0) { }

void aspect_properties_generator::
populate(const unsigned int position, result_type& v) {
    v.is_floating_point(create_bool(position + 0));
    v.requires_static_reference_equals(create_bool(position + 1));
}

aspect_properties_generator::result_type
aspect_properties_generator::create(const unsigned int position) {
    aspect_properties r;
    aspect_properties_generator::populate(position, r);
    return r;
}

aspect_properties_generator::result_type*
aspect_properties_generator::create_ptr(const unsigned int position) {
    aspect_properties* p = new aspect_properties();
    aspect_properties_generator::populate(position, *p);
    return p;
}

aspect_properties_generator::result_type
aspect_properties_generator::operator()() {
    return create(position_++);
}

} } } }
