/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2014 Marco Craveiro <marco.craveiro@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include <sstream>
#include <iostream>
#include <boost/exception/all.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include "dogen/utility/log/life_cycle_manager.hpp"
#include "dogen/utility/log/severity_level.hpp"
#include "dogen/utility/log/logger.hpp"
#include "dogen/version.hpp"
#include "dogen/stitcher/program_options_parser.hpp"
#include "dogen/stitcher/parser_validation_error.hpp"
#include "dogen/stitch/types/parser.hpp"
#include "dogen/stitch/types/instantiator.hpp"
#include "dogen/stitch/types/workflow.hpp"
#include "dogen/stitcher/workflow.hpp"

using namespace dogen::utility::log;

namespace {

auto lg(logger_factory("stitcher"));
const std::string log_file_prefix("log/dogen.stitcher.");
const std::string get_help("Use --help option to see usage instructions.");
const std::string stitcher_product("Dogen Stitcher v" DOGEN_VERSION);
const std::string usage_error_msg("Usage error: ");
const std::string fatal_error_msg("Fatal Error: " );
const std::string log_file_msg("See the log file for details: ");
const std::string errors_msg(" finished with errors.");

/**
 * @brief Print the program's help text.
 */
void help(const std::string& d) {
    std::cout << "Dogen Stitcher." << std::endl
              << "Generates C++ code from a stitch text template."
              << std::endl << std::endl << d << std::endl;
}

/**
 * @brief Print the program's version details.
 */
void version() {
    std::cout << stitcher_product << std::endl
              << "Copyright (C) 2015-2017 Domain Driven Consulting Plc."
              << std::endl
              << "Copyright (C) 2012-2015 Marco Craveiro." << std::endl
              << "License: GPLv3 - GNU GPL version 3 or later "
              << "<http://gnu.org/licenses/gpl.html>."
              << std::endl;
}

}

namespace dogen {
namespace stitcher {

workflow::workflow() : can_log_(false) { }

void workflow::
initialise_template_name(const dogen::options::stitching_options& o) {
    const boost::filesystem::path p(o.target());
    template_name_ = p.stem().filename().string();
}

boost::optional<options::stitching_options> workflow::
generate_stitching_options_activity(const int argc, const char* argv[]) const {
    program_options_parser p(argc, argv);
    p.help_function(help);
    p.version_function(version);
    boost::optional<options::stitching_options> r(p.parse());
    return r;
}

void workflow::
initialise_logging_activity(const options::stitching_options& o) {
    const auto sev(utility::log::to_severity_level(o.log_level()));
    if (!template_name_.empty())
        log_file_name_ = log_file_prefix + template_name_ + ".log";
    else
        log_file_name_ = log_file_prefix + "all_templates.log";

    life_cycle_manager lcm;
    lcm.initialise(log_file_name_, sev);
    can_log_ = true;
}

void workflow::stitch_activity(const options::stitching_options& o) const {
    BOOST_LOG_SEV(lg, info) << stitcher_product << " started.";
    stitch::workflow w;
    w.execute(o.target());
    BOOST_LOG_SEV(lg, info) << stitcher_product << " finished.";
}

void workflow::report_exception_common() const {
    if (can_log_) {
        BOOST_LOG_SEV(lg, warn) << stitcher_product << errors_msg;
        std::cerr << log_file_msg << "'" << log_file_name_.generic_string()
                  << "' " << std::endl;
    }

    if (template_name_.empty())
        return;

    std::cerr << "Failed to generate template: '" << template_name_ << "'."
              << std::endl;
}

void workflow::report_exception(const std::exception& e) const {
    /* we must catch by std::exception and cast the boost
     * exception here; if we were to catch boost exception, we
     * would not have access to the what() method and thus could
     * not provide a user-friendly message to the console.
     */
    const auto be(dynamic_cast<const boost::exception* const>(&e));
    if (be && can_log_) {
        BOOST_LOG_SEV(lg, error) << "Error: "
                                 << boost::diagnostic_information(*be);
    }

    if (be) {
        const auto file_name(boost::get_error_info<stitch::error_in_file>(e));
        if (file_name)
            std::cerr << *file_name;

        const auto line_number(boost::get_error_info<stitch::error_at_line>(e));
        if (line_number)
            std::cerr << ":" << *line_number << ": error: ";
    }
    std::cerr << e.what() << std::endl;
    report_exception_common();
}

void workflow::report_exception() const {
    std::cerr << "Stitcher was forced to terminate." << std::endl;
    report_exception_common();
}

int workflow::execute(const int argc, const char* argv[]) {
    try {
        const auto o(generate_stitching_options_activity(argc, argv));

        /* can only happen if the options are valid but do not
         * require any action.
         */
        if (!o)
            return 0;

        const auto& s(*o);
        initialise_template_name(s);
        initialise_logging_activity(s);
        stitch_activity(s);
    } catch (const stitcher::parser_validation_error& e) {
        /* log known not to be initialised as we are still parsing
         * command line options.
         */
        std::cerr << usage_error_msg << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        report_exception(e);
        return 1;
    } catch(...) {
        report_exception();
        return 1;
    }
    return 0;
}

} }
