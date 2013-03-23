/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_CPP_FORMATTERS_CPP_DOMAIN_HEADER_HPP
#define DOGEN_CPP_FORMATTERS_CPP_DOMAIN_HEADER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <boost/filesystem/path.hpp>
#include "dogen/sml/types/category_types.hpp"
#include "dogen/cpp/types/formatters/cpp_indenter.hpp"
#include "dogen/cpp/types/formatters/cpp_utility.hpp"
#include "dogen/cpp/types/view_models/class_view_model.hpp"
#include "dogen/cpp/types/view_models/exception_view_model.hpp"
#include "dogen/cpp/types/view_models/enumeration_view_model.hpp"
#include "dogen/cpp/types/view_models/file_view_model.hpp"
#include "dogen/cpp/types/formatters/file_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class domain_header : public file_formatter {
public:
    typedef view_models::exception_view_model exception_view_model;
    typedef view_models::enumeration_view_model enumeration_view_model;
    typedef view_models::class_view_model class_view_model;
    typedef view_models::file_view_model file_view_model;

public:
    domain_header() = delete;
    domain_header(const domain_header&) = default;
    domain_header(domain_header&&) = default;
    domain_header& operator=(const domain_header&) = default;

public:
    domain_header(std::ostream& stream, const bool disable_complete_constructor,
        const bool use_integrated_io, const bool disable_io,
        const bool serialization_enabled);

    virtual ~domain_header() noexcept {}

public:
    static file_formatter::shared_ptr create(std::ostream& stream,
        const bool disable_complete_constructor, const bool use_integrated_io,
        const bool disable_io, const bool disable_serialization);

private:
    void inserter_operator(const class_view_model& vm);
    void equality_operator(const class_view_model& vm);
    void swap_method(const class_view_model& vm);
    void class_declaration(const sml::category_types ct,
        const class_view_model& vm);
    void format_main(const sml::category_types ct, const class_view_model& vm);

private:
    void format_class(const file_view_model& vm);
    void format_enumeration(const file_view_model& vm);
    void format_exception(const file_view_model& vm);

public:
    virtual void format(const file_view_model& vm) override;

private:
    std::ostream& stream_;
    cpp_indenter indenter_;
    cpp_utility utility_;
    const bool disable_complete_constructor_;
    const bool use_integrated_io_;
    const bool disable_io_;
    const bool disable_serialization_;
};

} } }

#endif
