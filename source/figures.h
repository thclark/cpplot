/*
 * figures.h Allows flexible plotting in c++ using Plotly
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

#ifndef CPPLOT_FIGURES_H
#define CPPLOT_FIGURES_H

#include <exception>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <bitset>
#include <Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <boost/any.hpp>
#include <cpr/cpr.h>
#include <json/single_include/nlohmann/json.hpp>
#include "exceptions.h"

using nlohmann::json;


namespace plotly {

    // Enumerate the different plot types that are possible with plotly
    enum PlotType { bar, scatter };

    // Base class for managing the figure creation process
    class Figure {

    private:

        json data = json::array();

    protected:

    public:

        Figure();

        // TODO layout class
        json layout = json::object();

//        // Figure name used in report tagging
//        std::string name = "";
//
//        // Short_caption used in report contents tables
//        std::string short_caption = "";
//
//        // Long caption used in report
//        std::string caption = "";

        // Add plot data to the figure
        void add(boost::any plot);

        // Write the figure to a file
        void write(std::string filename);

    };

    // TODO Represent Figure class in ostream
    /*
    ::std::ostream& operator<<(::std::ostream& os, const Figure& fig) {
        // Represent in logs or ostream
        return os << "debug statement for figure class";
    }
    */

//    Figure::Figure();
//
//    void Figure::add(boost::any plot);
//
//    void Figure::write(std::string filename);

} // end namespace plotly

#endif // CPPLOT_FIGURES_H
