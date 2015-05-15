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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/sml/types/string_converter.hpp"
#include "dogen/cpp/types/formattables/building_error.hpp"
#include "dogen/cpp/types/formattables/path_derivatives_repository_factory.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.formattables.path_derivatives_expander"));

const std::string model_module_not_found("Model module not found for model: ");

}

namespace dogen {
namespace cpp {
namespace formattables {


dynamic::schema::object formatter_properties_repository_factory::
obtain_root_object(const sml::model& m) const {
    BOOST_LOG_SEV(lg, debug) << "Obtaining model's root object.";

    const auto i(m.modules().find(m.name()));
    if (i == m.modules().end()) {
        const auto n(sml::string_converter::convert(m.name()));
        BOOST_LOG_SEV(lg, error) << model_module_not_found << n;
        BOOST_THROW_EXCEPTION(building_error(model_module_not_found + n));
    }

    BOOST_LOG_SEV(lg, debug) << "Obtained model's root object.";
    return i->second.extensions();
}

path_derivatives_repository formatter_properties_repository_factory::
create_path_derivatives_repository(const config::cpp_options& opts,
    const dynamic::schema::repository& rp, const dynamic::schema::object& ro,
    const formatters::container& fc,
    const sml::model& m) const {
    path_derivatives_repository_factory f;
    return f.make(opts, rp, ro, fc, m);
}

inclusion_directives_repository formatter_properties_repository_factory::
create_inclusion_directives_repository(
    const path_derivatives_repository& /*pdrp*/) const {
    // FIXME: this logic move to factory
    inclusion_directives_repository r;
    return r;
    // for (const auto& pd : pdrp.path_derivatives_by_qname()) {
    // }
}


formatter_properties_repository formatter_properties_repository_factory::
make(const config::cpp_options& opts, const dynamic::schema::repository& rp,
    const formatters::container& fc, const sml::model& m) const {

    const auto ro(obtain_root_object(m));
    create_path_derivatives_repository(opts, rp, ro, fc, m);

    formatter_properties_repository r;
    return r;
}

} } }