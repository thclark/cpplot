/*
 * scatter.cpp Implementation of ScatterPlot methods and operators
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

#include <json/single_include/nlohmann/json.hpp>
#include "bar.h"
#include "figures.h"


using nlohmann::json;


namespace plotly {

void to_json(json& j, const BarPlot& p) {
    /* Turn plot type and data into a valid json string. Produces figure data JSON similar to:
     *      {"x": ["giraffes", "orangutans", "monkeys"],
     *       "y": [20, 14, 23],
     *       "type": "bar"}
     */
    j = json{{"x",  p.x}, {"y", p.y}, {"type", "bar"}};
}

std::string ScatterPlot::toJson() {
    /* Turn plot type, data and layout into valid json strings.
     */

    // TODO Get the correct type representation from a template enumeration
    std::string type_string = "\"scatter\"";

    // Assemble into a json string representing the graph
    // TODO serialise the data structure properly
    return "{\"type\": " + type_string + ", \"data\": " + data.toJson() + layout + "}";

}

std::string ScatterPlot::ScatterData::toJson() {
    // TODO serialise the data structure properly
    return "data_scatter_json";
}

} // end namespace plotly
