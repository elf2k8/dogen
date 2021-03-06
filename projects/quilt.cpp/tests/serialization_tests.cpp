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
#include <boost/test/unit_test.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/yarn/serialization/element_ser.hpp"
#include "dogen/yarn/io/element_io.hpp"
#include "dogen/quilt.cpp/types/all.hpp"
#include "dogen/quilt.cpp/io/all_io.hpp"
#include "dogen/quilt.cpp/test_data/all_td.hpp"
#include "dogen/quilt.cpp/serialization/all_ser.hpp"
#include "dogen/quilt.cpp/serialization/registrar_ser.hpp"

template<typename Archive> void register_types(Archive& ar) {
    dogen::quilt::cpp::register_types<Archive>(ar);
}

namespace {

const std::string empty;
const std::string test_module("quilt.cpp");
const std::string test_suite("serialization_tests");

}

using namespace dogen::quilt::cpp;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(serialization_tests)

BOOST_AUTO_TEST_CASE(validate_serialization) {
    SETUP_TEST_LOG("validate_serialization");

    roundtrip_type<formattables::model_generator>();
    roundtrip_type<formattables::formattable_generator>();
    roundtrip_type<formattables::odb_properties_generator>();
    roundtrip_type<formattables::element_properties_generator>();
    roundtrip_type<formattables::global_enablement_configuration_generator>();
    roundtrip_type<formattables::artefact_properties_generator>();
    roundtrip_type<formattables::helper_properties_generator>();
    roundtrip_type<formattables::aspect_properties_generator>();
    roundtrip_type<formattables::facet_properties_generator>();
    roundtrip_type<formattables::helper_descriptor_generator>();
    roundtrip_type<formattables::streaming_properties_generator>();
    roundtrip_type<formattables::locator_configuration_generator>();
    roundtrip_type<formattables::locator_facet_configuration_generator>();
    roundtrip_type<formattables::locator_archetype_configuration_generator>();
    roundtrip_type<formattables::inclusion_directive_configuration_generator>();
    roundtrip_type<fabric::registrar_generator>();
    roundtrip_type<fabric::cmakelists_generator>();
    roundtrip_type<fabric::odb_options_generator>();
    roundtrip_type<fabric::master_header_generator>();
    roundtrip_type<fabric::forward_declarations_generator>();

    boost::shared_ptr<dogen::yarn::element> el(
        fabric::registrar_generator::create_ptr(2));

    dogen::utility::test::serialization_tester<
        boost::shared_ptr<dogen::yarn::element>
    >::all_roundtrips_produce_the_same_entity(el);
}

BOOST_AUTO_TEST_SUITE_END()
