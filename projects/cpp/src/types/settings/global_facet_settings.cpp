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
#include "dogen/cpp/types/settings/global_facet_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

global_facet_settings::global_facet_settings()
    : enabled_(static_cast<bool>(0)) { }

global_facet_settings::global_facet_settings(
    const bool enabled,
    const std::string& directory,
    const std::string& postfix,
    const std::set<std::string>& integrated_facets)
    : enabled_(enabled),
      directory_(directory),
      postfix_(postfix),
      integrated_facets_(integrated_facets) { }

void global_facet_settings::swap(global_facet_settings& other) noexcept {
    using std::swap;
    swap(enabled_, other.enabled_);
    swap(directory_, other.directory_);
    swap(postfix_, other.postfix_);
    swap(integrated_facets_, other.integrated_facets_);
}

bool global_facet_settings::operator==(const global_facet_settings& rhs) const {
    return enabled_ == rhs.enabled_ &&
        directory_ == rhs.directory_ &&
        postfix_ == rhs.postfix_ &&
        integrated_facets_ == rhs.integrated_facets_;
}

global_facet_settings& global_facet_settings::operator=(global_facet_settings other) {
    using std::swap;
    swap(*this, other);
    return *this;
}

bool global_facet_settings::enabled() const {
    return enabled_;
}

void global_facet_settings::enabled(const bool v) {
    enabled_ = v;
}

const std::string& global_facet_settings::directory() const {
    return directory_;
}

std::string& global_facet_settings::directory() {
    return directory_;
}

void global_facet_settings::directory(const std::string& v) {
    directory_ = v;
}

void global_facet_settings::directory(const std::string&& v) {
    directory_ = std::move(v);
}

const std::string& global_facet_settings::postfix() const {
    return postfix_;
}

std::string& global_facet_settings::postfix() {
    return postfix_;
}

void global_facet_settings::postfix(const std::string& v) {
    postfix_ = v;
}

void global_facet_settings::postfix(const std::string&& v) {
    postfix_ = std::move(v);
}

const std::set<std::string>& global_facet_settings::integrated_facets() const {
    return integrated_facets_;
}

std::set<std::string>& global_facet_settings::integrated_facets() {
    return integrated_facets_;
}

void global_facet_settings::integrated_facets(const std::set<std::string>& v) {
    integrated_facets_ = v;
}

void global_facet_settings::integrated_facets(const std::set<std::string>&& v) {
    integrated_facets_ = std::move(v);
}

} } }