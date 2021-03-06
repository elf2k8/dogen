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
#include "dogen/stitch/test_data/line_td.hpp"
#include "dogen/stitch/test_data/text_template_body_td.hpp"
#include "dogen/annotations/test_data/scribble_group_td.hpp"

namespace {

dogen::annotations::scribble_group
create_dogen_annotations_scribble_group(const unsigned int position) {
    return dogen::annotations::scribble_group_generator::create(position);
}

dogen::stitch::line
create_dogen_stitch_line(const unsigned int position) {
    return dogen::stitch::line_generator::create(position);
}

std::list<dogen::stitch::line> create_std_list_dogen_stitch_line(unsigned int position) {
    std::list<dogen::stitch::line> r;
    for (unsigned int i(0); i < 4; ++i) {
        r.push_back(create_dogen_stitch_line(position + i));
    }
    return r;
}

}

namespace dogen {
namespace stitch {

text_template_body_generator::text_template_body_generator() : position_(0) { }

void text_template_body_generator::
populate(const unsigned int position, result_type& v) {
    v.scribble_group(create_dogen_annotations_scribble_group(position + 0));
    v.lines(create_std_list_dogen_stitch_line(position + 1));
}

text_template_body_generator::result_type
text_template_body_generator::create(const unsigned int position) {
    text_template_body r;
    text_template_body_generator::populate(position, r);
    return r;
}

text_template_body_generator::result_type*
text_template_body_generator::create_ptr(const unsigned int position) {
    text_template_body* p = new text_template_body();
    text_template_body_generator::populate(position, *p);
    return p;
}

text_template_body_generator::result_type
text_template_body_generator::operator()() {
    return create(position_++);
}

} }
