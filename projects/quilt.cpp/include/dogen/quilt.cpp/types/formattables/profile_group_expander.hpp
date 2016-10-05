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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_EXPANDER_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_PROFILE_GROUP_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <forward_list>
#include <boost/filesystem/path.hpp>
#include "dogen/quilt.cpp/types/formattables/model.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class profile_group_expander {
private:
    typedef std::unordered_map<std::string, formattables::profile_group>
    profile_group_types;

    profile_group_types hydrate(
        const std::forward_list<boost::filesystem::path>&
        data_directories) const;

    profile_group_types merge(const profile_group_types& pgs) const;

    void populate_model(const profile_group_types& pgs, model& fm) const;

public:
    void expand(
        const std::forward_list<boost::filesystem::path>& data_directories,
        model& fm) const;
};

} } } }

#endif
