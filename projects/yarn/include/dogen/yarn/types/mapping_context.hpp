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
#ifndef DOGEN_YARN_TYPES_MAPPING_CONTEXT_HPP
#define DOGEN_YARN_TYPES_MAPPING_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/serialization/mapping_context_fwd_ser.hpp"

namespace dogen {
namespace yarn {

class mapping_context final {
public:
    mapping_context() = default;
    mapping_context(const mapping_context&) = default;
    mapping_context(mapping_context&&) = default;
    ~mapping_context() = default;

public:
    mapping_context(
        const std::unordered_map<std::string, dogen::yarn::name>& translations,
        const std::unordered_set<std::string>& erasures,
        const std::unordered_map<std::string, dogen::yarn::name>& injections);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::mapping_context& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::mapping_context& v, unsigned int version);

public:
    const std::unordered_map<std::string, dogen::yarn::name>& translations() const;
    std::unordered_map<std::string, dogen::yarn::name>& translations();
    void translations(const std::unordered_map<std::string, dogen::yarn::name>& v);
    void translations(const std::unordered_map<std::string, dogen::yarn::name>&& v);

    const std::unordered_set<std::string>& erasures() const;
    std::unordered_set<std::string>& erasures();
    void erasures(const std::unordered_set<std::string>& v);
    void erasures(const std::unordered_set<std::string>&& v);

    const std::unordered_map<std::string, dogen::yarn::name>& injections() const;
    std::unordered_map<std::string, dogen::yarn::name>& injections();
    void injections(const std::unordered_map<std::string, dogen::yarn::name>& v);
    void injections(const std::unordered_map<std::string, dogen::yarn::name>&& v);

public:
    bool operator==(const mapping_context& rhs) const;
    bool operator!=(const mapping_context& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mapping_context& other) noexcept;
    mapping_context& operator=(mapping_context other);

private:
    std::unordered_map<std::string, dogen::yarn::name> translations_;
    std::unordered_set<std::string> erasures_;
    std::unordered_map<std::string, dogen::yarn::name> injections_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::mapping_context& lhs,
    dogen::yarn::mapping_context& rhs) {
    lhs.swap(rhs);
}

}

#endif
