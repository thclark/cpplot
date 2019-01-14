/*
 * scatter.h ScatterPlot data class
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

#ifndef CPPLOT_SCATTER_H
#define CPPLOT_SCATTER_H

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
#include <cpr/cpr.h>
#include <json/single_include/nlohmann/json.hpp>
#include "exceptions.h"

using nlohmann::json;


namespace plotly {


class ScatterPlot {
public:

    // TODO remove defaults
    // TODO remove eigen dependency and use std::vector<boost::any>
    Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(3, 0.0, 2.0);
    Eigen::VectorXd y = Eigen::VectorXd::LinSpaced(3, 1.0, 3.0);

    ScatterPlot() {}

};


void to_json(json& j, const ScatterPlot& p) {
    /* Turn plot type and data into a valid json string. Produces figure data JSON similar to:
     *      {"x": [24.23, 3.4, 8.4],
     *       "y": [20.1, 14.4, 23.3],
     *       "type": "scatter"}
     */
    j = json{{"x",  p.x}, {"y", p.y}, {"type", "scatter"}};
}


} // end namespace plotly

#endif //CPPLOT_SCATTER_H
