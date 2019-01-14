/*
 * figures_test.cpp - Unit testing for the cpplot library
 *
 * References:
 *
 *   [1]
 *
 * Future Improvements:
 *
 *   [1]
 *
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-8 T Clark. All Rights Reserved.
 *
 */

#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <limits>
#include <exception>
#include <stdlib.h>
#include <Eigen/Dense>
#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>
#include "figures.h"
#include "exceptions.h"
#include "gtest/gtest.h"
#include "glog/logging.h"


using namespace Eigen;
using namespace google;
using namespace plotly;


// TODO inherit from a base test class
class FigureTest : public ::testing::Test {

protected:

    /* Returns environment variable TEST_DATA_DIR, which contains a system-dependent path to a directory where test
     * fixture data may be stored, and which may be used to write output test files. If no environment variable is set,
     * defaults to the current working directory in which the test framework is being run.
     * A trailing slash is always appended.
     */
    std::string TestDataDir() {

        const char *tmp = std::getenv("TEST_DATA_DIR");
        std::string test_data_dir;
        if (tmp) {
            std::string s(tmp);
            test_data_dir = s;
        } else {
            boost::filesystem::path cwd(boost::filesystem::current_path());
            test_data_dir = cwd.string();
        }
        if (!boost::algorithm::ends_with(test_data_dir, "/")) {
            test_data_dir.append("/");
        }

        return test_data_dir;
    }

    // Define the matrix output format for this set of tests
    IOFormat test_format;

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right before each test)

        IOFormat debug_format(FullPrecision, 0, ", ", ";\n", "", "", "[", "]");
        test_format = debug_format;

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right before the destructor)
    }

};


// Test creation of a bar chart
TEST_F(FigureTest, test_bar_chart) {

    // Example bar chart
    BarPlot p = BarPlot();
    std::cout << p.toJson() << std::endl;

    // Write it to disk
    Figure<BarPlot> fig = Figure<BarPlot>(p);
    fig.write(TestDataDir().append("test_bar_chart.json"));

}


//// Test the osstream operator works. Bloody thing.
//TEST_F(FigureTest, test_figure_ostream) {
//
//    // Example bar chart
//    BarPlot p = BarPlot();
//    std::cout << p.toJson() << std::endl;
//
//    // Send to plotly for rendering
//    Figure<BarPlot> fig = Figure<BarPlot>(p);
//
//    std::cout << fig << std::endl;
//
//}
