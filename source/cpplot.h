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
// Moved file from #include <json/single_include/nlohmann/json.hpp> to avoid having to install json as a dependency whenever we install or use cpplot
#include <json.hpp>
#include "exceptions.h"
#include "eigen.h"
#include "layout.h"
#include "plot_types/bar.h"
#include "plot_types/scatter.h"
#include "plot_types/surface.h"


namespace cpplot {

    // Enumerate the different plot types that are possible with plotly
    enum PlotType { bar, scatter };

    // Base class for managing the figure creation process
    class Figure {

    protected:

        nlohmann::json data;
        nlohmann::json layout;
        nlohmann::json meta;

    public:

        Figure(){
            data = nlohmann::json::array();
            layout = nlohmann::json::object();
            meta = nlohmann::json::object();
        }

        /// Optional metadata - Figure ID
        std::string id = "";

        /// Optional metadata - Figure name used for display (e.g. in cpplot-viewer)
        std::string name = "";

        /// Optional metadata - Short_caption used in report contents tables
        std::string short_caption = "";

        /// Optional metadata - Long caption used beside the figure (e.g. in a report)
        std::string caption = "";

        /** @brief Add plot data to the figure
         *
         * @tparam T type of the plot data to add
         * @param plot
         */
        template <class T>
        void add(T &plot) {
            // Data is a json array of plot data
            data.push_back(plot);
        }

        /** @brief Add layout data to the figure
         *
         *
         */
        void setLayout(Layout &lay) {
            layout.update(lay);
        }

        /** @brief Write the figure to a file
         *
         * **CAUTION:** Overwrites any existing file contents.
         *
         * @param[in] file_name The file name to write to, including any absolute or relative path
         * @param[in] append_extension If true, a .json extension will be appended to file_name (if not already present)
         * @param[in] print_to_stdout Default false. If true, the json will also be printed to std::cout (useful for debugging)
         */
        void write(std::string file_name, bool append_extension = true, bool print_to_stdout = false){

            // Compile metadata into a json object. NB any other fields already added to meta will be kept, allowing addition of arbitrary metadata to figures.
            meta["id"] = id;
            meta["name"] = name;
            meta["caption"] = caption;
            meta["short_caption"] = short_caption;

            // Convert the figure to JSON: copy each value into the JSON object
            nlohmann::json j;
            j["data"] = data;
            j["layout"] = layout;
            j["meta"] = meta;

            // Get the file name
            if (!boost::algorithm::ends_with(file_name, ".json") && append_extension) {
                file_name.append(".json");
            }

            // Open the file and stream the string into it, overwriting any existing contents
            std::ofstream file;
            file.open(file_name);
            file << j;
            file.close();

            // Also write to stdout
            if (print_to_stdout) {
                std::cout << "Figure json:" << std::endl << j << std::endl;
            }

        }
        // TODO Represent Figure class in ostream
        /*
        ::std::ostream& operator<<(::std::ostream& os, const Figure& fig) {
            // Represent in logs or ostream
            return os << "debug statement for figure class";
        }
        */

    };

    // TODO Represent Figure class in ostream
    /*
    ::std::ostream& operator<<(::std::ostream& os, const Figure& fig) {
        // Represent in logs or ostream
        return os << "debug statement for figure class";
    }
    */


} // end namespace

#endif // CPPLOT_FIGURES_H
