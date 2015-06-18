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
#include "dogen/dynamic/test_data/value_td.hpp"
#include "dogen/dynamic/test_data/boolean_td.hpp"

namespace {

bool create_bool(const unsigned int position) {
    return (position % 2) == 0;
}

}

namespace dogen {
namespace dynamic {

boolean_generator::boolean_generator() : position_(0) { }

void boolean_generator::
populate(const unsigned int position, result_type& v) {
    dogen::dynamic::value_generator::populate(position, v);
    v.content(create_bool(position + 0));
}

boolean_generator::result_type
boolean_generator::create(const unsigned int position) {
    boolean r;
    boolean_generator::populate(position, r);
    return r;
}

boolean_generator::result_type*
boolean_generator::create_ptr(const unsigned int position) {
    boolean* p = new boolean();
    boolean_generator::populate(position, *p);
    return p;
}

boolean_generator::result_type
boolean_generator::operator()() {
    return create(position_++);
}

} }
