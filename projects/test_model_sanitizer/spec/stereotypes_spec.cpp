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
#include <boost/test/unit_test.hpp>
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/test/asserter.hpp"
#include "dogen/utility/test/logging.hpp"
#include "dogen/utility/test/canned_tests.hpp"
#include "dogen/stereotypes/types/all.hpp"
#include "dogen/stereotypes/io/all_io.hpp"
#include "dogen/stereotypes/serialization/all_ser.hpp"
#include "dogen/test_model_sanitizer/register_types.hpp"
#include "dogen/stereotypes/test_data/all_td.hpp"
#include "dogen/stereotypes/hash/all_hash.hpp"

namespace {

const std::string empty;
const std::string test_module("test_model_sanitizer");
const std::string test_suite("stereotypes");

}

using dogen::utility::test::asserter;
using namespace dogen::stereotypes;
using namespace dogen::utility::test;

BOOST_AUTO_TEST_SUITE(stereotypes)

BOOST_AUTO_TEST_CASE(validate_equality) {
    SETUP_TEST_LOG("validate_equality");
    test_equality<entity_generator>();
    test_equality<value_generator>();
    test_equality<immutable_four_generator>();
    test_equality<immutable_one_non_primitive_generator>();
    test_equality<immutable_one_primitive_generator>();
    test_equality<immutable_two_generator>();
    test_equality<fluent_generator>();
}

BOOST_AUTO_TEST_CASE(validate_serialisation) {
    SETUP_TEST_LOG("validate_serialisation");
    rountrip_type<entity_generator>();
    rountrip_type<value_generator>();
    rountrip_type<immutable_four_generator>();
    rountrip_type<immutable_one_non_primitive_generator>();
    rountrip_type<immutable_one_primitive_generator>();
    rountrip_type<immutable_two_generator>();
    rountrip_type<fluent_generator>();
}

BOOST_AUTO_TEST_CASE(validate_hashing) {
    SETUP_TEST_LOG("validate_hashing");
    test_hashing<entity_generator>();
    test_hashing<value_generator>();
    test_hashing<immutable_four_generator>();
    test_hashing<immutable_one_non_primitive_generator>();
    test_hashing<immutable_one_primitive_generator>();
    test_hashing<immutable_two_generator>();
    test_hashing<fluent_generator>();
}

BOOST_AUTO_TEST_CASE(validate_swap) {
    SETUP_TEST_LOG("validate_hashing");
    test_swap<entity_generator>();
    test_swap<value_generator>();
    test_swap<fluent_generator>();
}

BOOST_AUTO_TEST_CASE(validate_io) {
    SETUP_TEST_LOG("validate_io");
    test_io<entity_generator>();
    test_io<value_generator>();
    test_io<immutable_four_generator>();
    test_io<immutable_one_non_primitive_generator>();
    test_io<immutable_one_primitive_generator>();
    test_io<immutable_two_generator>();
    test_io<immutable_zero_generator>();
    test_io<fluent_generator>();
}


BOOST_AUTO_TEST_CASE(setting_properties_using_the_fluent_interface_produces_expected_result) {
    SETUP_TEST_LOG("setting_properties_using_the_fluent_interface_produces_expected_result");

    const value z(15);
    const std::string s("a string");
    const fluent e(1234, s, z);
    fluent a;
    a.prop_0(1234).prop_1(s).prop_2(z);
    BOOST_CHECK(asserter::assert_equals(e, a));
}

BOOST_AUTO_TEST_CASE(versioned_stereotype_results_in_new_property_named_version) {
    SETUP_TEST_LOG("versioned_stereotype_results_in_new_property_named_version");

    versioned v;
    v.version(10);
}

BOOST_AUTO_TEST_SUITE_END()
