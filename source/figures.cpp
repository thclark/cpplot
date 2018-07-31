/*
 * figures.cpp Implementation of Figure and associated classes for plotting with Plotly from C++
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

#include "figures.h"

namespace plotly {

    std::string BarPlot::toJson() {
        /* Turn plot type, data and layout into valid json strings. Produces figure JSON similar to:
         *      fig = {"data": [{"x": ["giraffes", "orangutans", "monkeys"],
         *             "y": [20, 14, 23],
         *             "type": "bar"}
         */

        // Get the correct type representation from the enumeration
        std::string type_string = "\"bar\"";
        // Assemble into a json string representing the graph
        // TODO serialise the data structure properly
        return "{\"type\": " + type_string + ", \"data\": " + data.toJson() + layout + "}";

    }

    std::string BarPlot::BarData::toJson() {
        // TODO serialise the data structure properly
        std::cout << "WARNING: hacking json contents in the toJson() method" << std::endl;
        return "[{\"x\": [\"cppgiraffes\", \"orangutans\", \"monkeys\"], \"y\": [20, 14, 23]";
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
