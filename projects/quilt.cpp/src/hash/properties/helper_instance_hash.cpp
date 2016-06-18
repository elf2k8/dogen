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
#include "dogen/quilt.cpp/hash/settings/helper_settings_hash.hpp"
#include "dogen/quilt.cpp/hash/properties/helper_instance_hash.hpp"
#include "dogen/quilt.cpp/hash/properties/helper_descriptor_hash.hpp"

namespace {

template <typename HashableType>
inline void combine(std::size_t& seed, const HashableType& value) {
    std::hash<HashableType> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

inline std::size_t hash_std_list_dogen_quilt_cpp_properties_helper_descriptor(const std::list<dogen::quilt::cpp::properties::helper_descriptor>& v) {
    std::size_t seed(0);
    for (const auto i : v) {
        combine(seed, i);
    }
    return seed;
}

}

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

std::size_t helper_instance_hasher::hash(const helper_instance& v) {
    std::size_t seed(0);

    combine(seed, v.descriptors());
    combine(seed, hash_std_list_dogen_quilt_cpp_properties_helper_descriptor(v.associated_helpers()));
    combine(seed, v.settings());

    return seed;
}

} } } }
