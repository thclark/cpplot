/*
 * bar.h Bar chart data class
 *
 * References:
 *
 *   [1]
 *
 * Future Improvements:
 *
 *   [1] 
 *
 * 
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-8 T Clark. All Rights Reserved.
 *
 */

#ifndef CPPLOT_BAR_H
#define CPPLOT_BAR_H

#include <exception>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string.h>
//#include <time.h>
//#include <iostream>
//#include <fstream>
//#include <bitset>
#include <Eigen/Dense>
#include <boost/any.hpp>
#include <json/single_include/nlohmann/json.hpp>


using nlohmann::json;


namespace plotly {


class BarPlot {
public:
    // TODO remove defaults
    std::vector<std::string> x = {"cppgiraffes", "orangutans", "monkeys"};

    // TODO remove eigen dependency and use std::vector<boost::any>
    Eigen::VectorXd y = Eigen::VectorXd::LinSpaced(3, 1.0, 3.0);

    BarPlot() {}

    BarPlot(const std::vector<boost::any> &x, const std::vector<boost::any> &y);

    std::string string() {
        json j(this);
        std::string tmp;
        return j.dump(4);
    }
};


BarPlot::BarPlot(const std::vector<boost::any> &x, const std::vector<boost::any> &y) {
    // TODO Check they're iterable and if not put the single items in an iterable container

}

void to_json(json &j, const BarPlot &p) {
    /* Turn plot type and data into a valid json string. Produces figure data JSON similar to:
     *      {"x": ["giraffes", "orangutans", "monkeys"],
     *       "y": [20, 14, 23],
     *       "type": "bar"}
     */
    j = json{{"x", p.x}, {"y", p.y}, {"type", "bar"}};
}


} // end namespace

#endif //CPPLOT_BAR_H
