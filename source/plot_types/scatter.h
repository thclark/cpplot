/*
 * scatter.h ScatterPlot data class
 * 
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-9 T Clark. All Rights Reserved.
 *
 */

#ifndef CPPLOT_SCATTER_H
#define CPPLOT_SCATTER_H

#include <vector>
#include <string.h>
#include <Eigen/Dense>
#include <json/single_include/nlohmann/json.hpp>

#include "eigen.h"
#include "exceptions.h"


namespace cpplot {


class ScatterPlot {

public:
    Eigen::VectorXd x;
    Eigen::VectorXd y;
    std::string type = "scatter";

    /** @brief Construct with default basic data (for test plots)
     */
    ScatterPlot() {
        x = Eigen::VectorXd::LinSpaced(3, 0.0, 2.0);
        y = Eigen::VectorXd::LinSpaced(3, 1.0, 3.0);
    }

};


/** @brief Serialise scatter plot data into a valid json string.
 *
 * Produces figure data JSON similar to:
 *      {"x": [24.23, 3.4, 8.4],
 *       "y": [20.1, 14.4, 23.3],
 *       "type": "scatter"}
 */
void to_json(nlohmann::json& j, const ScatterPlot& p) {

    nlohmann::json x;
    nlohmann::json y;
    to_json(x, p.x);
    to_json(y, p.y);
    j["x"] = x;
    j["y"] = y;
    j["type"] = p.type;
}


} // end namespace

#endif //CPPLOT_SCATTER_H
