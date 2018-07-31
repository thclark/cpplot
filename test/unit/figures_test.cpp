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
#include "figures.h"
#include "exceptions.h"
#include "gtest/gtest.h"
#include "glog/logging.h"


using namespace Eigen;
using namespace google;
using namespace plotly;


class FigureTest : public ::testing::Test {

protected:

    /* Returns environment variable TEST_DATA_DIR, which contains the system-dependent path to the test data file,
     * or defaults to the current directory. NB the variable must contain trailing '/'.
     * TODO inherit from a base test class
     */
    std::string TestFixtureDir() {
        // TODO use the boost library to make the variable independent of trailing '/'.
        const char *test_data_dir = std::getenv("TEST_DATA_DIR");
        return test_data_dir ? test_data_dir : "./";
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

    // Send to plotly for rendering
    Figure<BarPlot> fig = Figure<BarPlot>(p);
    fig.plot();

    std::cout << "Figure plotlyUrl(): " << fig.plotlyUrl() <<  std::endl;

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
