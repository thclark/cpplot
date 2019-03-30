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
    fig.write(TestDataDir().append("test_scatter_plot.json"), true, true);

}


TEST_F(FigureTest, test_wide_coloured_dashed_scatter_plot) {

    ScatterPlot p = ScatterPlot();
    p.setWidth(1);
    p.setDash("dash");
    p.setColor("#e377c2");
    Figure fig = Figure();
    fig.add(p);
    fig.write(TestDataDir().append("test_wide_coloured_dashed_scatter_plot"), true, true);

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
    lay.xTitle("ecks");
    lay.yTitle("why");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_layout_plot.json"), true, true);

}


TEST_F(FigureTest, test_3d_axes_labels) {

    Figure fig = Figure();
    SurfacePlot p = SurfacePlot();
    fig.add(p);
    Layout lay = Layout("Graph Title");
    lay.xTitle("ecks");
    lay.yTitle("why");
    lay.zTitle("zedd");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_3d_axes_labels.json"), true, true);

}


TEST_F(FigureTest, test_layout_no_title) {

    Figure fig = Figure();
    ScatterPlot p = ScatterPlot();
    fig.add(p);
    Layout lay = Layout();
    lay.xTitle("ecks");
    lay.yTitle("why");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_layout_no_title_plot.json"), true, true);

}


TEST_F(FigureTest, test_latex_labels) {

    Figure fig = Figure();
    ScatterPlot p = ScatterPlot();
    p.name = "$\\eta_{12}$";
    fig.add(p);
    Layout lay = Layout();
    lay.xTitle("$x + y$");
    lay.yTitle("$d, r \\\\text{(solar radius)}$");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_latex_labels.json"), true, true);

}


TEST_F(FigureTest, test_log_axes) {

    Figure fig = Figure();
    ScatterPlot p = ScatterPlot();
    p.x = Eigen::RowVectorXd::LinSpaced(100, 1, 100000);
    p.y = 2.0 * p.x;
    p.name = "relationship";
    fig.add(p);
    Layout lay = Layout();
    lay.xTitle("x");
    lay.yTitle("y");
    lay.xLog();
    lay.yLog();
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_log_axes.json"), true, true);

}


TEST_F(FigureTest, test_wolfgang) {

    double dx = 1.2;
    double dy = 1.1;


    Figure fig = Figure();
    ScatterPlot h = ScatterPlot();
    h.x = Eigen::ArrayXd(6);
    h.x << 0, 0, 0, 0.8, 0.8, 0.8;
    h.y = Eigen::ArrayXd(6);
    h.y << 0, 1, 0.5, 0.5, 1, 0;
    h.y = h.y.array() + dy;
    h.name = "H";
    fig.add(h);

    ScatterPlot a = ScatterPlot();
    a.x = Eigen::ArrayXd(6);
    a.x << 0, 0.4, 0.5, 0.3, 0.5, 0.8;
    a.x = a.x.array() + dx;
    a.y = Eigen::ArrayXd(6);
    a.y << 0, 1, 0.5, 0.5, 0.5, 0;
    a.y = a.y.array() + dy;
    a.name = "A";
    fig.add(a);

    ScatterPlot p = ScatterPlot();
    p.x = Eigen::ArrayXd(5);
    p.x << 0, 0, 0.8, 0.8, 0;
    p.x = p.x.array() + 2*dx;
    p.y = Eigen::ArrayXd(5);
    p.y << 0, 1, 1, 0.6, 0.6;
    p.y = p.y.array() + dy;
    p.name = "P";
    fig.add(p);

    ScatterPlot p2 = ScatterPlot();
    p2.x = Eigen::ArrayXd(5);
    p2.x << 0, 0, 0.8, 0.8, 0;
    p2.x = p2.x.array() + 3*dx;
    p2.y = Eigen::ArrayXd(5);
    p2.y << 0, 1, 1, 0.6, 0.6;
    p2.y = p2.y.array() + dy;
    p2.name = "P";
    fig.add(p2);

    ScatterPlot y = ScatterPlot();
    y.x = Eigen::ArrayXd(6);
    y.x << 0, 0, 0.8, 0.8, 0.8, 0.4;
    y.x = y.x.array() + 4*dx;
    y.y = Eigen::ArrayXd(6);
    y.y << 1, 0.6, 0.6, 1, 0, 0;
    y.y = y.y.array() + dy;
    y.name = "Y";
    fig.add(y);

    ScatterPlot b = ScatterPlot();
    b.x = Eigen::ArrayXd(6);
    b.x << 0, 0, 0.8, 0, 0.8, 0;
    b.x = b.x.array() + 6*dx;
    b.y = Eigen::ArrayXd(6);
    b.y << 0, 1, 0.66, 0.5, 0.33, 0;
    b.y = b.y.array() + dy;
    b.name = "B";
    fig.add(b);

    ScatterPlot i = ScatterPlot();
    i.x = Eigen::ArrayXd(6);
    i.x << 0, 0.8, 0.4, 0.4, 0, 0.8;
    i.x = i.x.array() + 7*dx;
    i.y = Eigen::ArrayXd(6);
    i.y << 1, 1, 1, 0, 0, 0;
    i.y = i.y.array() + dy;
    i.name = "I";
    fig.add(i);

    ScatterPlot r = ScatterPlot();
    r.x = Eigen::ArrayXd(6);
    r.x << 0, 0, 0.8, 0.8, 0, 0.8;
    r.x = r.x.array() + 8*dx;
    r.y = Eigen::ArrayXd(6);
    r.y << 0, 1, 1, 0.6, 0.6, 0;
    r.y = r.y.array() + dy;
    r.name = "R";
    fig.add(r);

    ScatterPlot t = ScatterPlot();
    t.x = Eigen::ArrayXd(7);
    t.x << 0.3, 0.3, 0, 0.8, 0.3, 0.3, 0.8;
    t.x = t.x.array() + 9*dx;
    t.y = Eigen::ArrayXd(7);
    t.y << 1, 0.6, 0.6, 0.6, 0.6, 0, 0;
    t.y = t.y.array() + dy;
    t.name = "T";
    fig.add(t);

    ScatterPlot h2 = ScatterPlot();
    h2.x = Eigen::ArrayXd(6);
    h2.x << 0, 0, 0, 0.8, 0.8, 0.8;
    h2.x = h2.x.array() + 10*dx;
    h2.y = Eigen::ArrayXd(6);
    h2.y << 0, 1, 0.5, 0.5, 1, 0;
    h2.y = h2.y.array() + dy;
    h2.name = "H";
    fig.add(h2);

    ScatterPlot d = ScatterPlot();
    d.x = Eigen::ArrayXd(5);
    d.x << 0, 0, 0.8, 0.8, 0;
    d.x = d.x.array() + 11*dx;
    d.y = Eigen::ArrayXd(5);
    d.y << 0, 1, 0.8, 0.2, 0;
    d.y = d.y.array() + dy;
    d.name = "D";
    fig.add(d);

    ScatterPlot a2 = ScatterPlot();
    a2.x = Eigen::ArrayXd(6);
    a2.x << 0, 0.4, 0.5, 0.3, 0.5, 0.8;
    a2.x = a2.x.array() + 12*dx;
    a2.y = Eigen::ArrayXd(6);
    a2.y << 0, 1, 0.5, 0.5, 0.5, 0;
    a2.y = a2.y.array() + dy;
    a2.name = "A";
    fig.add(a2);

    ScatterPlot y2 = ScatterPlot();
    y2.x = Eigen::ArrayXd(6);
    y2.x << 0, 0, 0.8, 0.8, 0.8, 0.4;
    y2.x = y2.x.array() + 13*dx;
    y2.y = Eigen::ArrayXd(6);
    y2.y << 1, 0.6, 0.6, 1, 0, 0;
    y2.y = y2.y.array() + dy;
    y2.name = "Y";
    fig.add(y2);

    ScatterPlot w = ScatterPlot();
    w.x = Eigen::ArrayXd(5);
    w.x << 0, 0.2, 0.4, 0.6, 0.8;
    w.x = w.x.array() + 0*dx;
    w.y = Eigen::ArrayXd(5);
    w.y << 1, 0, 0.6, 0, 1;
    w.name = "W";
    fig.add(w);

    ScatterPlot o = ScatterPlot();
    o.x = Eigen::ArrayXd(5);
    o.x << 0, 0.8, 0.8, 0, 0;
    o.x = o.x.array() + 1*dx;
    o.y = Eigen::ArrayXd(5);
    o.y << 0, 0, 1, 1, 0;
    o.name = "O";
    fig.add(o);

    ScatterPlot l = ScatterPlot();
    l.x = Eigen::ArrayXd(3);
    l.x << 0, 0, 0.8;
    l.x = l.x.array() + 2*dx;
    l.y = Eigen::ArrayXd(3);
    l.y << 1, 0, 0;
    l.name = "L";
    fig.add(l);

    ScatterPlot f = ScatterPlot();
    f.x = Eigen::ArrayXd(6);
    f.x << 0, 0, 0.8, 0, 0, 0.6;
    f.x = f.x.array() + 3*dx;
    f.y = Eigen::ArrayXd(6);
    f.y << 0, 1, 1, 1, 0.6, 0.6;
    f.name = "F";
    fig.add(f);

    ScatterPlot g = ScatterPlot();
    g.x = Eigen::ArrayXd(8);
    g.x << 0, 0.8, 0.8, 0, -0.05, 0, 0, 0.8;
    g.x = g.x.array() + 4*dx;
    g.y = Eigen::ArrayXd(8);
    g.y << 0, 0, 1, 1, 1.05, 1, 0.6, 0.6;
    g.name = "G";
    fig.add(g);

    ScatterPlot a3 = ScatterPlot();
    a3.x = Eigen::ArrayXd(6);
    a3.x << 0, 0.4, 0.5, 0.3, 0.5, 0.8;
    a3.x = a3.x.array() + 5*dx;
    a3.y = Eigen::ArrayXd(6);
    a3.y << 0, 1, 0.5, 0.5, 0.5, 0;
    a3.name = "A";
    fig.add(a3);
    ScatterPlot n = ScatterPlot();
    n.x = Eigen::ArrayXd(4);
    n.x << 0, 0, 0.8, 0.8;
    n.x = n.x.array() + 6*dx;
    n.y = Eigen::ArrayXd(4);
    n.y << 0, 1, 0, 1;
    n.name = "N";
    fig.add(n);

    ScatterPlot g2 = ScatterPlot();
    g2.x = Eigen::ArrayXd(8);
    g2.x << 0, 0.8, 0.8, 0, -0.05, 0, 0, 0.8;
    g2.x = g2.x.array() + 7*dx;
    g2.y = Eigen::ArrayXd(8);
    g2.y << 0, 0, 1, 1, 1.05, 1, 0.6, 0.6;
    g2.name = "G";
    fig.add(g2);

    Layout lay = Layout();
    lay.xTitle("Wishes");
    lay.yTitle("Best");
    fig.setLayout(lay);
    fig.write(TestDataDir().append("test_wolfgang.json"), true, true);

}
