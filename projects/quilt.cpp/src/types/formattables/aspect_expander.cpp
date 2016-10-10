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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_map_io.hpp"
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/dynamic/io/field_definition_io.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/quilt.cpp/io/formattables/aspect_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/aspect_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("quilt.cpp.formattables.aspect_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream&
operator<<(std::ostream& s, const aspect_expander::field_definitions& v) {
    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "aspect_expander::field_definitions\"" << ", "
      << "\"requires_manual_default_constructor\": "
      << v.requires_manual_default_constructor << ", "
      << "\"requires_manual_move_constructor\": "
      << v.requires_manual_move_constructor << ", "
      << "\"requires_stream_manipulators\": "
      << v.requires_stream_manipulators
      << " }";

    return s;
}

aspect_expander::field_definitions
aspect_expander::make_field_definitions(const dynamic::repository& drp) const {
    field_definitions r;

    const dynamic::repository_selector rs(drp);
    typedef traits::cpp::aspect aspect;

    const auto& rmdc(aspect::requires_manual_default_constructor());
    r.requires_manual_default_constructor = rs.select_field_by_name(rmdc);

    const auto& rmmc(aspect::requires_manual_move_constructor());
    r.requires_manual_move_constructor = rs.select_field_by_name(rmmc);

    const auto& rsm(aspect::requires_stream_manipulators());
    r.requires_stream_manipulators = rs.select_field_by_name(rsm);

    return r;
}

boost::optional<aspect_properties> aspect_expander::
make_aspect_properties(const field_definitions& fds,
    const dynamic::object& o) const {
    aspect_properties r;

    const dynamic::field_selector fs(o);
    bool found_any(false);

    if (fs.has_field(fds.requires_manual_default_constructor))
        found_any = true;

    r.requires_manual_default_constructor(
        fs.get_boolean_content_or_default(
            fds.requires_manual_default_constructor));

    if (fs.has_field(fds.requires_manual_move_constructor))
        found_any = true;

    r.requires_manual_move_constructor(
        fs.get_boolean_content_or_default(
            fds.requires_manual_move_constructor));

    if (fs.has_field(fds.requires_stream_manipulators))
        found_any = true;

    r.requires_stream_manipulators(
        fs.get_boolean_content_or_default(
            fds.requires_stream_manipulators));

    if (found_any)
        return r;

    return boost::optional<aspect_properties>();
}

aspect_expander::aspect_properties_type
aspect_expander::obtain_aspect_properties(const dynamic::repository& drp,
    const std::unordered_map<std::string, formattable>& formattables) const {

    BOOST_LOG_SEV(lg, debug) << "Started creating aspect configuration.";

    const auto fds(make_field_definitions(drp));
    aspect_properties_type r;
    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        const auto& segment(*formattable.master_segment());
        const auto ac(make_aspect_properties(fds, segment.extensions()));
        if (ac)
            r[id] = *ac;
    }
    BOOST_LOG_SEV(lg, debug) << "Finished creating aspect configurations. "
                             << "Result: " << r;
    return r;
}

void aspect_expander::walk_name_tree(const yarn::name_tree& nt,
    const bool is_top_level, const aspect_properties_type& element_aps,
    aspect_properties& ap) const {

    for (const auto& c : nt.children())
        walk_name_tree(c, false/*is_top_level*/, element_aps, ap);

    if (is_top_level && nt.is_current_simple_type())
        ap.requires_manual_default_constructor(true);

    const auto i(element_aps.find(nt.current().id()));
    if (i == element_aps.end())
        return;

    const auto element_ap(i->second);
    if (element_ap.requires_stream_manipulators())
        ap.requires_stream_manipulators(true);

    if (!is_top_level)
        return;

    if (element_ap.requires_manual_default_constructor())
        ap.requires_manual_default_constructor(true);

    if (element_ap.requires_manual_move_constructor())
        ap.requires_manual_move_constructor(true);
}

aspect_properties
aspect_expander::compute_aspect_properties(
    const aspect_properties_type& element_aps,
    const std::list<yarn::attribute>& attr) const {

    aspect_properties r;
    for (const auto a : attr) {
        const auto& nt(a.parsed_type());
        walk_name_tree(nt, true/*is_top_level*/, element_aps, r);
    }
    return r;
}

void aspect_expander::populate_aspect_properties(
    const aspect_properties_type& element_aps,
    std::unordered_map<std::string, formattable>& formattables) const {

    for (auto& pair : formattables) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);
        auto& eprops(formattable.element_properties());

        /*
         * We only want to process the master segment; the
         * extensions can be ignored.
         */
        auto segment(formattable.master_segment());

        /*
         * We are only interested in yarn objects; all other
         * element types do not need helpers.
         */
        const auto ptr(dynamic_cast<const yarn::object*>(segment.get()));
        if (ptr == nullptr)
            continue;

        /*
         * We only need to generate the aspect configuration for
         * elements of the target model. However, we can't perform
         * this after reduction because the aspect configurations must
         * be build prior to reduction or else we will not get aspects
         * for referenced models.
         */
        if (ptr->generation_type() == yarn::generation_types::no_generation)
            continue;

        /*
         * Update the aspect configuration.
         */
        const auto& attr(ptr->local_attributes());
        const auto element_ap(compute_aspect_properties(element_aps, attr));
        eprops.aspect_properties(element_ap);
    }
}

void aspect_expander::
expand(const dynamic::repository& drp, model& fm) const {
    const auto element_aps(obtain_aspect_properties(drp, fm.formattables()));
    populate_aspect_properties(element_aps, fm.formattables());
}

} } } }
