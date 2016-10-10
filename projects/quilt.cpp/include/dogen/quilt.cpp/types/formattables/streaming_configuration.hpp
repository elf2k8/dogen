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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_STREAMING_CONFIGURATION_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_STREAMING_CONFIGURATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/quilt.cpp/serialization/formattables/streaming_configuration_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class streaming_configuration final {
public:
    streaming_configuration(const streaming_configuration&) = default;
    streaming_configuration(streaming_configuration&&) = default;
    ~streaming_configuration() = default;

public:
    streaming_configuration();

public:
    streaming_configuration(
        const bool requires_quoting,
        const std::string& string_conversion_method,
        const bool remove_unprintable_characters);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::streaming_configuration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::streaming_configuration& v, unsigned int version);

public:
    bool requires_quoting() const;
    void requires_quoting(const bool v);

    const std::string& string_conversion_method() const;
    std::string& string_conversion_method();
    void string_conversion_method(const std::string& v);
    void string_conversion_method(const std::string&& v);

    bool remove_unprintable_characters() const;
    void remove_unprintable_characters(const bool v);

public:
    bool operator==(const streaming_configuration& rhs) const;
    bool operator!=(const streaming_configuration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(streaming_configuration& other) noexcept;
    streaming_configuration& operator=(streaming_configuration other);

private:
    bool requires_quoting_;
    std::string string_conversion_method_;
    bool remove_unprintable_characters_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::streaming_configuration& lhs,
    dogen::quilt::cpp::formattables::streaming_configuration& rhs) {
    lhs.swap(rhs);
}

}

#endif