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
#include <Eigen/Dense>
#include <nlohmann/json.hpp>


using nlohmann::json;


namespace cpplot {


class BarPlot {
public:

    std::vector<std::string> x;
    Eigen::VectorXd y;
    std::string type = "bar";
    std::string name = "";

    /** @brief Construct with default basic data (for test plots)
     */
    BarPlot() {
        x = {"cppgiraffes", "orangutans", "monkeys"};
        y = Eigen::VectorXd::LinSpaced(3, 2.0, 3.0);
    }

};


/** @brief Serialise bar plot data into a valid json string.
 *
 * Produces figure data JSON similar to:
 *      {"x": ["giraffes", "orangutans", "monkeys"],
 *       "y": [20.1, 14.4, 23.3],
 *       "type": "bar"}
 */
void to_json(nlohmann::json& j, const BarPlot& p) {

    nlohmann::json y;
    to_json(y, p.y);
    j["x"] = p.x;
    j["y"] = y;
    j["type"] = p.type;
    if (!p.name.empty()) {
        j["name"] = p.name;
    }

}


} // end namespace

#endif //CPPLOT_BAR_H
