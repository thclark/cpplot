/*
 * layout.h
 * 
 * Author:              Tom Clark  (thclark @ github)
 *
 * Copyright (c) 2019 Octue Ltd. All Rights Reserved.
 *
 */

#ifndef CPPLOT_LAYOUT_H
#define CPPLOT_LAYOUT_H

#include <exception>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <Eigen/Dense>
#include <json/single_include/nlohmann/json.hpp>


using nlohmann::json;


namespace cpplot {


/** @brief Enum of the three possible axis directions, X, Y, Z.
 */
enum AxisDirection { X, Y, Z};

/** @brief Axis class for use in layout of plots.
 *
 * Serialises to something like:
 * @code
 *     "xaxis": {"title": "x1"}
 * @endcode
 */
class Axis {
public:
    // Allow the serialiser function to access protected members
    friend void to_json(nlohmann::json& j, const Axis& p);

    explicit Axis(const AxisDirection dir) : direction(dir){
        switch(dir){
            case X:
                key = "xaxis";
                break;
            case Y:
                key = "yaxis";
                break;
            case Z:
                key = "zaxis";
                break;
        }
    };

    /** @brief Sets the direction of the axis, as X, Y, or Z
     *
     * @param dir Axis direction (an enum X, Y or Z)
     */
    void setDirection(AxisDirection dir) {
        direction = dir;
    };

    void setTitle(std::string label) {
        title = label;
    };

    void setLog() {
        is_log = true;
    };

    AxisDirection getDirection() {
        return direction;
    };

    std::string getTitle() {
        return title;
    };

    bool isLog() {
        return is_log;
    };

protected:
    AxisDirection direction;
    std::string title;
    std::string key;
    bool is_log = false;
};


/** @brief Serialise axis into a valid json string.
 *
 * Produces json like:
 * @code
 *     "xaxis": {"title": "x1"}
 * @endcode
 */
void to_json(nlohmann::json& j, const Axis& p) {
    nlohmann::json axis;
    axis["title"] = p.title;
    if (p.is_log) {
        axis["type"] = "log";
    };
    j[p.key] = axis;
}


class Layout {
public:

    // Allow the serialiser function to access protected members
    friend void to_json(nlohmann::json& j, const Layout& p);

    /** @brief Construct with default basic data (for test plots)
     *
     * Example use:
     * @code
     * Layout my_layout = Layout("a graph title"); // Default constructor Layout() also works
     * my_layout.xLabel("ecks");
     * my_layout.yLabel("why";
     * @endcode
     *
     *
     */
    explicit Layout(const std::string title="", const bool is_scene=false) : title(title), is_scene(is_scene) {};

    /** @brief get an axis in the layout by its direction. Optionally, create if not found.
     *
     * Example use:
     * @code
     * Layout my_layout = Layout("a graph title"); // Default constructor Layout() also works
     * axis = my_layout.getAxis(X); // raises error
     * axis = my_layout.getAxis(X, true); // creates the axis and adds it to the layout
     * @endcode
     *
     * @param dir
     * @return
     */
    Axis* getAxis(const AxisDirection &dir, bool create=false) {
        for (auto &axis: axes) {
            if (axis.getDirection() == dir) {
                return &axis;
            };
        };
        if (create) {
            Axis ax(dir);
            axes.push_back(ax);
            // If a Z axis is created, turn the plot into a 3D scene
            if (dir == Z) {
                is_scene = true;
            }
            return &axes.back();
        } else {
            InvalidAxisException e;
            throw (e);
        };
    }

    /** @brief set the title of the x axis
     *
     * @param[in] label the title of the axis. Can use latex within dollar signs, like "Normalised distance \$\eta\$"
     */
    void xTitle(const std::string label) {
        AxisDirection dir = X;
        getAxis(dir, true)->setTitle(label);
    }

    /** @brief set the title of the y axis
     *
     * @param[in] label the title of the axis. Can use latex within dollar signs, like "Normalised distance \$\eta\$"
     */
    void yTitle(const std::string label) {
        AxisDirection dir = Y;
        getAxis(dir, true)->setTitle(label);
    }

    /** @brief set the title of the z axis
     *
     * @param[in] label the title of the axis. Can use latex within dollar signs, like "Normalised distance \$\eta\$"
     */
    void zTitle(const std::string label) {
        AxisDirection dir = Z;
        getAxis(dir, true)->setTitle(label);
    }

    /** @brief change the type of the x axis from its default, 'linear', to 'log'
     */
    void xLog() {
        AxisDirection dir = X;
        getAxis(dir, true)->setLog();
    }

    /** @brief change the type of the y axis from its default, 'linear', to 'log'
     */
    void yLog() {
        AxisDirection dir = Y;
        getAxis(dir, true)->setLog();
    }

    /** @brief change the type of the z axis from its default, 'linear', to 'log'
     */
    void zLog() {
        AxisDirection dir = Z;
        getAxis(dir, true)->setLog();
    }

protected:

    std::vector<Axis> axes;
    std::string title;
    bool is_scene;

};


/** @brief Serialise layout into a valid json string.
 *
 */
void to_json(nlohmann::json& j, const Layout& p) {

    if (!p.title.empty()) {
        j["title"] = p.title;
    };
    nlohmann::json axes;
    for (auto &axis : p.axes) {
        nlohmann::json ax;
        to_json(ax, axis);
        axes.update(ax);
    };
    if (p.is_scene) {
        j["scene"] = axes;
    } else {
        j.update(axes);
    };
};


}; // end namespace cpplot

#endif // CPPLOT_LAYOUT_H
