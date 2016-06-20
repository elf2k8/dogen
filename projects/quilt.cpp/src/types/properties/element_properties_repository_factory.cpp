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
#include "dogen/quilt.cpp/io/properties/element_properties_repository_io.hpp"
#include "dogen/quilt.cpp/types/properties/helper_properties_repository_factory.hpp"
#include "dogen/quilt.cpp/types/properties/element_properties_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "quilt.cpp.properties.element_properties_repository_factory"));

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

helper_properties_repository element_properties_repository_factory::
create_helper_properties(const yarn::model& m,
    const settings::helper_settings_repository& hsrp) const {
    helper_properties_repository_factory f;
    return f.make(m, hsrp);
}

element_properties_repository element_properties_repository_factory::merge(
    const helper_properties_repository& hprp,
    const formatter_properties_repository& fprp) const {

    element_properties_repository r;
    for(const auto& pair : fprp.by_id()) {
        element_properties& ep(r.by_id()[pair.first]);
        ep.formatter_properties(pair.second);

        const auto i(hprp.by_id().find(pair.first));
        if (i != hprp.by_id().end())
            ep.helper_properties(i->second);
    }
    return r;
}

element_properties_repository element_properties_repository_factory::make(
    const settings::helper_settings_repository& hsrp,
    const formatter_properties_repository& fprp,
    const yarn::model& m) const {
    const auto hprp(create_helper_properties(m, hsrp));
    const auto r(merge(hprp, fprp));
    BOOST_LOG_SEV(lg, debug) << "Finished computing element properties:" << r;
    return r;
}

} } } }