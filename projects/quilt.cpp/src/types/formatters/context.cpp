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
#include "dogen/quilt.cpp/types/formatters/context.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

context::context(
    const formattables::element_configuration& element_configuration,
    const formattables::model& fm,
    const std::unordered_map<std::string, std::unordered_map<std::string,
    std::list<std::shared_ptr<helper_formatter_interface>>>>& helpers)
    : element_configuration_(element_configuration), model_(fm),
      helpers_(helpers) { }

const formattables::element_configuration&
context::element_configuration() const {
    return element_configuration_;
}

const formattables::model& context::model() const {
    return model_;
}

const std::unordered_map<
    std::string,
    std::unordered_map<
        std::string, std::list<std::shared_ptr<helper_formatter_interface>>>>&
context::helpers() const {
    return helpers_;
}

} } } }
