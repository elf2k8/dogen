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
#ifndef DOGEN_ANNOTATIONS_TYPES_TEXT_HPP
#define DOGEN_ANNOTATIONS_TYPES_TEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/annotations/types/value.hpp"
#include "dogen/annotations/serialization/text_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Field can hold text.
 */
class text final : public dogen::annotations::value {
public:
    text() = default;
    text(const text&) = default;
    text(text&&) = default;

    virtual ~text() noexcept { }

public:
    explicit text(const std::string& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::text& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::text& v, unsigned int version);

public:
    using value::accept;

    virtual void accept(const value_visitor& v) const override;
    virtual void accept(value_visitor& v) const override;
    virtual void accept(const value_visitor& v) override;
    virtual void accept(value_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief Text value.
     */
    /**@{*/
    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);
    /**@}*/

public:
    bool operator==(const text& rhs) const;
    bool operator!=(const text& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::annotations::value& other) const override;

public:
    void swap(text& other) noexcept;
    text& operator=(text other);

private:
    std::string content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::text& lhs,
    dogen::annotations::text& rhs) {
    lhs.swap(rhs);
}

}

#endif
