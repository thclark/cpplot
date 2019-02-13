/*
 * scatter.h ScatterPlot data class
 * 
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-9 T Clark. All Rights Reserved.
 *
 */

#ifndef CPPLOT_SURFACE_H
#define CPPLOT_SURFACE_H

#include <vector>
#include <string.h>
#include <Eigen/Dense>
#include <json/single_include/nlohmann/json.hpp>

#include "eigen.h"
#include "exceptions.h"


namespace cpplot {

/** @brief Default color scales available in plotly
 * TODO refactor these to separate file and allow fo custom colourmaps
 */
enum ColorScale {
   Blackbody,
   Bluered,
   Blues,
   Earth,
   Electric,
   Greens,
   Greys,
   Hot,
   Jet,
   Picnic,
   Portland,
   Rainbow,
   RdBu,
   Reds,
   Viridis,
   YlGnBu,
   YYlOrRd
};
const std::vector<std::string> colour_names = {
    "Blackbody",
    "Bluered",
    "Blues",
    "Earth",
    "Electric",
    "Greens",
    "Greys",
    "Hot",
    "Jet",
    "Picnic",
    "Portland",
    "Rainbow",
    "RdBu",
    "Reds",
    "Viridis",
    "YlGnBu",
    "YlOrRd"
};

/** @brief Serialise color scale data into a valid json field or fields
 *
 * Produces figure data JSON similar to:
 *
 */
void to_json(nlohmann::json& j, const ColorScale& c) {
    j["colorscale"] = colour_names[c];
}


class SurfacePlot {

public:

    ColorScale colorscale = YlGnBu;
    Eigen::ArrayXXd x;
    Eigen::ArrayXXd y;
    Eigen::ArrayXXd z;
    std::string type = "surface";

    /** @brief Construct with default basic data (for test plots)
     */
    SurfacePlot() {
        x = Eigen::RowVectorXd::LinSpaced(3, -1.5, 0.6).replicate(3,1).array();
        y = Eigen::VectorXd::LinSpaced(3, -1.26, 1.26).replicate(1,3).array();
        z = x.pow(2) + y;
    };

};


/** @brief Serialise surface plot data into a valid json string.
 *
 * Produces figure data JSON similar to:
 *
 */
void to_json(nlohmann::json& j, const SurfacePlot& p) {

    nlohmann::json x;
    nlohmann::json y;
    nlohmann::json z;
    to_json(x, p.x);
    to_json(y, p.y);
    to_json(z, p.z);
    j["x"] = x;
    j["y"] = y;
    j["z"] = z;
    to_json(j, p.colorscale);
    j["type"] = p.type;
}


} // end namespace

#endif //CPPLOT_SURFACE_H
