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

    Figure::Figure() {
        // Constructor

    }

    // TODO Represent Figure class in ostream
    /*
    ::std::ostream& operator<<(::std::ostream& os, const Figure& fig) {
        // Represent in logs or ostream
        return os << "debug statement for figure class";
    }
    */

    void Figure::add(boost::any plot) {
        // Add a plot to the list
        data.push_back(plot.json());
    }


    void Figure::write(std::string filename) {
        // Write the figure data to a file, which is automatically appended with '.json' if it isn't already.

        // Convert the figure to JSON: copy each value into the JSON object
        json j;
        j["data"] = data;
        j["layout"] = layout;

        // Get the file name
        if (!boost::algorithm::ends_with(filename, ".json")) {
            filename.append(".json");
        }

        // Open the file and stream the string into it, overwriting any existing contents
        std::ofstream file;
        file.open(filename);
        file << j;
        file.close();

    }

} // end namespace plotly

#endif // CPPLOT_FIGURES_H
