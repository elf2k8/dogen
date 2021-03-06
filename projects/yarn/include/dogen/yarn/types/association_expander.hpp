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
#ifndef DOGEN_YARN_TYPES_ASSOCIATION_EXPANDER_HPP
#define DOGEN_YARN_TYPES_ASSOCIATION_EXPANDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <unordered_set>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/object.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/intermediate_model.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Information expander that specialises in indexing
 * associations for objects.
 *
 * @section yarn_association_expander_0 Requirements
 *
 * The expansion of local attributes is expected to have taken place.
 *
 * @section yarn_attribute_indexer_1 Indexing Process
 *
 * The expander goes through all attributes in objects and, for every
 * name tree, unpacks all the associations implied by their presence.
 *
 * Associations are of two types: @e regular or @e weak. This
 * distinction is required due to the usage of the association at code
 * generation time.
 *
 * A @e regular association means a full type definition is required
 * to be available due to the association. A @e weak association means
 * that the type is used via pointer and as such a forward declaration
 * may suffice.
 */
class association_expander {
private:
    /**
     * @brief Removes duplicate names, preserving the original order
     * of elements in the list.
     *
     * @param names list of names to process
     * @param processed list of names that have already been processed
     * somewhere else, if any.
     */
    void remove_duplicates(std::list<name>& names,
        std::unordered_set<name> processed =
        std::unordered_set<name>()) const;

    /**
     * @brief Walks through the name tree, picking up associations as
     * it goes along.
     */
    void walk_name_tree(const intermediate_model& im, object& o,
        const name_tree& nt, const bool inherit_opaqueness_from_parent) const;

private:
    /**
     * @brief Expands a specific object.
     */
    void expand_object(const intermediate_model& im, object& o) const;

public:
    /**
     * @brief Expands all association relationships.
     */
    void expand(intermediate_model& im) const;
};

} }

#endif
