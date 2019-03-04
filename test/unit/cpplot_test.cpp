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
#include <Eigen/Dense>
#include <boost/stacktrace.hpp>
#include <boost/filesystem.hpp>
#include "cpplot.h"
#include "eigen.h"
#include "exceptions.h"
#include "gtest/gtest.h"
#include "glog/logging.h"


using namespace Eigen;
using namespace google;
using namespace cpplot;


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
        std::cout << "Test Data Output Dir is: " << TestDataDir() << std::endl;

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right before the destructor)
    }

};


TEST_F(FigureTest, test_bar_plot) {

    BarPlot p = BarPlot();
    Figure fig = Figure();
    fig.add(p);
    std::cout << "Writing to TestDataDir(): " << TestDataDir() << std::endl;
    fig.write(TestDataDir().append("test_bar_plot.json"));

}


TEST_F(FigureTest, test_scatter_plot) {

    ScatterPlot p = ScatterPlot();
    Figure fig = Figure();
    fig.add(p);
    fig.write(TestDataDir().append("test_scatter_plot.json")), true, true;

}


TEST_F(FigureTest, test_bar_and_scatter_plot) {

    Figure fig = Figure();
    BarPlot p1 = BarPlot();
    fig.add(p1);
    ScatterPlot p2 = ScatterPlot();
    fig.add(p2);
    std::cout << "Writing to TestDataDir(): " << TestDataDir() << std::endl;
    fig.write(TestDataDir().append("test_bar_and_scatter_plot.json"), true, true);

}

TEST_F(FigureTest, test_scatter_with_legend_plot) {

    Figure fig = Figure();
    ScatterPlot p1 = ScatterPlot();
    p1.name = "my first trace";
    fig.add(p1);
    ScatterPlot p2 = ScatterPlot();
    p2.name = "my second trace";
    fig.add(p2);
    std::cout << "Writing to TestDataDir(): " << TestDataDir() << std::endl;
    fig.write(TestDataDir().append("test_scatter_with_legend_plot.json"), true, true);

}


TEST_F(FigureTest, test_surface_plot) {

    Figure fig = Figure();
    SurfacePlot p = SurfacePlot();
    fig.add(p);
    fig.write(TestDataDir().append("test_surface_plot.json"), true, true);

}


TEST_F(FigureTest, test_mandelbrot_plot) {

    Figure fig = Figure();
    SurfacePlot p = SurfacePlot();

    int height = 600;
    int width = 600;
    int max_iterations = 16;

    p.x = Eigen::RowVectorXd::LinSpaced(width, -1.5, 0.6).replicate(height, 1).array();
    p.y = Eigen::VectorXd::LinSpaced(height, -1.26, 1.26).replicate(1, width).array();
    p.z = Eigen::ArrayXXd(width, height);

    // Loop to produce the fractal set
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            double a = p.x(i,j);
            double b = p.y(i,j);
            double xn = 0.0;
            double yn = 0.0;
            int k = 1;
            while ((k <= max_iterations) && ((pow(xn, 2.0) - pow(yn, 2.0)) < 4.0)) {
                double xnew = pow(xn, 2.0) - pow(yn, 2.0) + a;
                double ynew = 2.0 * xn * yn + b;
                xn = xnew;
                yn = ynew;
                k = k + 1;
            };
            p.z(i,j) = k;
        };
    };

    fig.add(p);
    fig.write(TestDataDir().append("test_mandelbrot_plot.json"), true, true);

}


TEST_F(FigureTest, test_eigen_serialiser) {

    nlohmann::json j;

    Eigen::ArrayXd arr1(5);
    arr1 << 0.001, 0.1, 0.3, 0.6, 1.0;
    nlohmann::json j1;
    to_json(j1, arr1);
    j["array1"] = j1;

    // NB Eigen uses column major indexing, but you have to init arrays in a row major way.
    Eigen::ArrayXXd arr2(5,2);
    arr2 << 0.0, 0.1,
            1.0, 1.1,
            2.0, 2.1,
            3.0, 3.1,
            4.0, 4.1;
    nlohmann::json j2;
    to_json(j2, arr2);
    j["array2"] = j2;
    std::cout << "array 0,1: " << arr2(0,1) << std::endl;
    std::cout << "array 1,0: " << arr2(1,0) << std::endl;

    std::cout << j.dump() << std::endl;
    EXPECT_EQ(j.dump(), "{\"array1\":[0.001,0.1,0.3,0.6,1],\"array2\":[[0,0.1],[1,1.1],[2,2.1],[3,3.1],[4,4.1]]}");

}


TEST_F(FigureTest, test_layout) {

    Figure fig = Figure();
    ScatterPlot p = ScatterPlot();
    fig.add(p);
    Layout lay = Layout("Graph Title");
    lay.xLabel("ecks");
    lay.yLabel("why");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_layout_plot.json"), true, true);

}


TEST_F(FigureTest, test_3d_axes_labels) {

    Figure fig = Figure();
    SurfacePlot p = SurfacePlot();
    fig.add(p);
    Layout lay = Layout("Graph Title");
    lay.xLabel("ecks");
    lay.yLabel("why");
    lay.zLabel("zedd");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_3d_axes_labels.json"), true, true);

}


TEST_F(FigureTest, test_layout_no_title) {

    Figure fig = Figure();
    ScatterPlot p = ScatterPlot();
    fig.add(p);
    Layout lay = Layout();
    lay.xLabel("ecks");
    lay.yLabel("why");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_layout_no_title_plot.json"), true, true);

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
