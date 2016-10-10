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
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/io/formattables/odb_properties_io.hpp"
#include "dogen/quilt.cpp/types/formattables/odb_expander.hpp"

namespace {

using namespace dogen::utility::log;
static logger
lg(logger_factory("quilt.cpp.formattables.odb_expander"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

std::ostream& operator<<(std::ostream& s,
    const odb_expander::field_definitions& v) {

    s << " { "
      << "\"__type__\": " << "\"dogen::quilt::cpp::formattables::"
      << "odb_expander::field_definitions\"" << ", "
      << "\"odb_pragma\": " << v.odb_pragma
      << " }";

    return s;
}

odb_expander::field_definitions odb_expander::
make_field_definitions(const dynamic::repository& drp) const {
    BOOST_LOG_SEV(lg, debug) << "Creating field definitions.";

    field_definitions r;
    const dynamic::repository_selector s(drp);
    const auto& cc(formatters::odb::traits::odb_pragma());
    r.odb_pragma = s.select_field_by_name(cc);

    BOOST_LOG_SEV(lg, debug) << "Created field definitions. Result: " << r;
    return r;
}

std::list<std::string> odb_expander::make_odb_pragmas(
    const field_definitions& fds, const dynamic::object& o) const {

    const dynamic::field_selector fs(o);
    if (!fs.has_field(fds.odb_pragma))
        return std::list<std::string>();

    return fs.get_text_collection_content(fds.odb_pragma);
}

boost::optional<odb_properties>
odb_expander::compute_odb_configuration(
    const field_definitions& fds, const yarn::object& o) const {

    odb_properties r;
    r.top_level_odb_pragmas(make_odb_pragmas(fds, o.extensions()));
    for (const auto& attr : o.local_attributes()) {
        const auto id(attr.name().id());
        const auto pragmas(make_odb_pragmas(fds, attr.extensions()));
        if (pragmas.empty())
            continue;

        r.attribute_level_odb_pragmas()[id] = pragmas;
    }

    const bool has_top_level_pragmas(!r.top_level_odb_pragmas().empty());
    const bool has_attribute_pragmas(!r.attribute_level_odb_pragmas().empty());
    const bool has_pragmas(has_top_level_pragmas || has_attribute_pragmas);
    if (has_pragmas)
        return r;

    return boost::optional<odb_properties>();
}

void odb_expander::
expand(const dynamic::repository& drp, model& fm) const {
    BOOST_LOG_SEV(lg, debug) << "Started expanding odb configuration.";
    const auto fds(make_field_definitions(drp));
    for (auto& pair : fm.formattables()) {
        const auto id(pair.first);
        BOOST_LOG_SEV(lg, debug) << "Procesing element: " << id;

        auto& formattable(pair.second);

        /*
         * We only want to process the master segment; the element
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

        const auto& o(*ptr);
        auto& eprops(formattable.element_properties());
        eprops.odb_properties(compute_odb_configuration(fds, o));
    }

    BOOST_LOG_SEV(lg, debug) << "Finished expanding odb configuration. ";
}

} } } }