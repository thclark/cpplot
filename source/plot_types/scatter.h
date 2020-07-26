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
#include <nlohmann/json.hpp>

#include "eigen.h"
#include "exceptions.h"


namespace cpplot {


/** @brief Class for managing and serialising properties of a line or lines.
 */
class Line {
public:
    // Allow the serialiser function to access protected members
    friend void to_json(nlohmann::json& j, const Line& p);

    /** @brief Constructor initialises a default Line type.
     */
    Line() {
        is_empty = true;
        width = -1; // This is "empty" i.e. not set.
    }

    /** @brief set solid line colour as a string.
     *
     * TODO Implement colour scaled values
     *
     * See https://plot.ly/ipython-notebooks/color-scales/#6-colors for an example of different colour scales and values available
     *
     * For reference, plotly's default colours are:
     * [
     *   '#1f77b4',  # muted blue
     *   '#ff7f0e',  # safety orange
     *   '#2ca02c',  # cooked asparagus green
     *   '#d62728',  # brick red
     *   '#9467bd',  # muted purple
     *   '#8c564b',  # chestnut brown
     *   '#e377c2',  # raspberry yogurt pink
     *   '#7f7f7f',  # middle gray
     *   '#bcbd22',  # curry yellow-green
     *   '#17becf'   # blue-teal
     * ]
     *
     * @param value std::string plotly colour value, e.g. setColor("#1f77b4")
     */
    void setColor(const std::string &value) {
        color = value;
        is_empty = false;
    }

    /** @brief set the line dash mode.
     *
     * Accepts "solid", "dot", "dash", "longdash", "dashdot", or "longdashdot" as dash_type input
     *
     * @param[in] value std::string The dash type to use
     */
    void setDash(const std::string &value) {
        // TODO check the string is valid, or enumerate.
        dash = value;
        is_empty = false;
    }

    /** @brief set the line width in pixels.
     *
     * @param[in] value int the width in pixels for the line
     */
    void setWidth(const int value) {
        width = value;
        is_empty = false;
    }

    /** @brief return boolean, false if any line properties are changed from default.
     */
    bool empty() const {
        return is_empty;
    }

protected:
    std::string dash;
    int width;
    std::string color;
    bool is_empty;

};


/** @brief Serialise line data into a valid json string.
 */
void to_json(nlohmann::json& j, const Line& p) {
    if (!p.dash.empty()) {
        j["dash"] = p.dash;
    };
    if (p.width != -1) {
        j["width"] = p.width;
    };
    if (!p.color.empty()) {
        j["color"] = p.color;
    }
}


class ScatterPlot {
public:
    // Allow the serialiser function to access protected members
    friend void to_json(nlohmann::json& j, const ScatterPlot& p);

    // TODO move to getter/setters
    Eigen::VectorXd x;
    Eigen::VectorXd y;
    std::string name = "";

    /** @brief Construct with default basic data (for test plots).
     */
    ScatterPlot() {
        x = Eigen::VectorXd::LinSpaced(3, 0.0, 2.0);
        y = Eigen::VectorXd::LinSpaced(3, 1.0, 3.0);
        line = Line();
    }

    /** @brief set solid line colour as a string.
     *
     *  See https://plot.ly/ipython-notebooks/color-scales/#6-colors for an example of different colour scales and values available
     *  See https://github.com/plotly/plotly.py/blob/master/plotly/colors.py#L83-L87 for plotly's master colour reference
     * For reference, plotly's default colours are:
     * [
     *   '#1f77b4',  # muted blue
     *   '#ff7f0e',  # safety orange
     *   '#2ca02c',  # cooked asparagus green
     *   '#d62728',  # brick red
     *   '#9467bd',  # muted purple
     *   '#8c564b',  # chestnut brown
     *   '#e377c2',  # raspberry yogurt pink
     *   '#7f7f7f',  # middle gray
     *   '#bcbd22',  # curry yellow-green
     *   '#17becf'   # blue-teal
     * ]
     *
     * @param value std::string plotly colour value, e.g. setColor("#1f77b4")
     */
    void setColor(const std::string &value) {
        line.setColor(value);
    }

    /** @brief set the line dash mode for this scatter plot.
     *
     * This is a helper function, which directly modifies a 'line' object, allowing a clean API for the user to update
     * scatter plots.
     *
     * Accepts "solid", "dot", "dash", "longdash", "dashdot", or "longdashdot"
     *
     * @param[in] dash_type std::string selected dash type
     */
    void setDash(const std::string &value) {
        line.setDash(value);
    }

    /** @brief set the line width in pixels.
     *
     * @param[in] value int the width in pixels for the line
     */
    void setWidth(const int value) {
        line.setWidth(value);
    }

protected:
    Line line;

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
    j["type"] = "scatter";
    if (!p.name.empty()) {
        j["name"] = p.name;
    }
    if (!p.line.empty()) {
        nlohmann::json line;
        to_json(line, p.line);
        j["line"] = line;
    }
};


} // end namespace

#endif //CPPLOT_SCATTER_H
