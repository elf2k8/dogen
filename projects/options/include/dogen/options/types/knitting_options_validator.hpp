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
#ifndef DOGEN_OPTIONS_TYPES_KNITTING_OPTIONS_VALIDATOR_HPP
#define DOGEN_OPTIONS_TYPES_KNITTING_OPTIONS_VALIDATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include "dogen/options/types/knitting_options.hpp"

namespace dogen {
namespace options {

class knitting_options_validator {
public:
    knitting_options_validator() = default;
    knitting_options_validator(const knitting_options_validator&) = default;
    ~knitting_options_validator() = default;
    knitting_options_validator(knitting_options_validator&&) = default;
    knitting_options_validator&
    operator=(const knitting_options_validator&) = default;

public:
    void validate(const knitting_options& s);
};

} }

#endif