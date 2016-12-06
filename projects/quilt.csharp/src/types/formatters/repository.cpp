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
#include "dogen/quilt.csharp/types/formatters/repository.hpp"
#include "dogen/quilt.csharp/types/formatters/artefact_formatter_interface.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

std::unordered_map<
    std::type_index,
    std::forward_list<std::shared_ptr<artefact_formatter_interface>>>&
repository::stock_artefact_formatters_by_type_index() {
    return stock_artefact_formatters_by_type_index_;
}

std::unordered_map<std::string, std::shared_ptr<artefact_formatter_interface>>&
repository::stock_artefact_formatters_by_archetype() {
    return stock_artefact_formatters_by_archetype_;
}

std::forward_list<std::shared_ptr<artefact_formatter_interface>>&
repository::stock_artefact_formatters() {
    return stock_artefact_formatters_;
}

const std::unordered_map<
    std::type_index,
    std::forward_list<std::shared_ptr<artefact_formatter_interface>>>&
repository::stock_artefact_formatters_by_type_index() const {
    return stock_artefact_formatters_by_type_index_;
}

const std::unordered_map<std::string,
                         std::shared_ptr<artefact_formatter_interface>>&
repository::stock_artefact_formatters_by_archetype() const {
    return stock_artefact_formatters_by_archetype_;
}

const std::forward_list<std::shared_ptr<artefact_formatter_interface>>&
repository::stock_artefact_formatters() const {
    return stock_artefact_formatters_;
}

} } } }
