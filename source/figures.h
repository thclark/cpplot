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
#include <bitset>
#include <Eigen/Dense>
#include <boost/algorithm/string.hpp>
#include <cpr/cpr.h>
#include <json/single_include/nlohmann/json.hpp>
#include "exceptions.h"

namespace plotly {

    // Encapsulate plotly config variables. Obtain credentials from the environment upon instantiation.
    struct Config {

        std::string url = "https://api.plot.ly/v2/";
        std::string user = "";
        std::string password = "";

        Config() {
            // Get configuration from environment variables. PLOTLY_URL is optional, allowing you to run your own server
            char *c_url = getenv("PLOTLY_URL");
            char *c_user = getenv("PLOTLY_USERNAME");
            char *c_password = getenv("PLOTLY_API_KEY");
            if ((c_user == NULL) || (c_password == NULL)) {
                InvalidOrMissingPlotlyCredentialsException e;
                throw (e);
            }
            if (c_url != NULL) {
                url = std::string(c_url);
            }
            user = std::string(c_user);
            password = std::string(c_password);
            if (url.back() == '/') {
                url.pop_back();
            }
        }

    };

    // Enumerate the different plot types that are possible with plotly
    enum PlotType { bar, scatter };

    class BarPlot {
    public:

        // Data container
        class BarData {
        public:
            std::vector<std::string> x = {"cppgiraffes", "orangutans", "monkeys"};
            Eigen::VectorXd y = Eigen::VectorXd::LinSpaced(3, 1.0, 3.0);
            std::string toJson();
        };

        // Properties
        PlotType type;
        BarData data;
        std::string layout;

        // Constructor
        BarPlot() {
            type = bar;
            data = BarData();
            layout = "";
        }

        // Serialiser
        std::string toJson();

    };

    class ScatterPlot {
    public:

        // Data container
        class ScatterData {
        public:
            Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(3, 0.0, 2.0);
            Eigen::VectorXd y = Eigen::VectorXd::LinSpaced(3, 1.0, 3.0);
            std::string toJson();
        };

        // Properties
        PlotType type;
        ScatterData data;
        std::string layout;

        // Constructor
        ScatterPlot() {
            type = scatter;
            data = ScatterData();
            layout = "";
        }

        // Serialiser
        std::string toJson();
    };

    // Base class for managing the figure creation process
    template <class ContentsType>
    class Figure {

    private:

        Config configuration;

        ContentsType contents;

        void setPlotlyIdFromUrl(std::string url);

    protected:

        // Plotly figure id
        std::string plotly_id;

        // Plotly username
        std::string plotly_usr;

        // Refers to the python plotly library used to generate the figure
        // TODO figure out how to get the version of plotly used to render the figure through their API; set it here
        std::string plotly_version = "unknown";

    public:

        Figure(ContentsType contents);

        // Gets the plotly URL string
        std::string plotlyUrl();

        // Figure name used in report tagging
        std::string name = "";

        // Short_caption used in report contents tables
        std::string short_caption = "";

        // Long caption used in report
        std::string caption = "";

        // Gets the plotly embed URL string
        std::string embedUrl();

        // Not implemented, as we don't use C++ to serve web content directly
        // html(self, **kwargs):

        // Gets the plotly PDF URL string (an expiring link to the pdf file containing the figure)
        std::string pdfUrl();

        // Update the figure json from the plotly server
        // Not implemented - one-way so far
        // void pull();

        // Plot the figure by POSTing its data to the plotly server
        void plot();

    };


//    // Represent Figure class in logs or ostream
//    template <class ContentsType>
//    ::std::ostream& operator<<(::std::ostream& os, const Figure<ContentsType>& fig);

    template <class ContentsType>
    Figure<ContentsType>::Figure(ContentsType contents) {

        // Get plotly server access configuration and credentials from the environment
        configuration = Config();

        contents = contents;

    }

    template <class ContentsType>
    std::string Figure<ContentsType>::plotlyUrl() {
        // Returns the URL to this figure on plotly, if the figure is rendered
        if (plotly_usr == "") {
            return "";
        }
        return configuration.url + "/~" + plotly_usr + "/" + plotly_id;
    }

//    template <class ContentsType>
//    ::std::ostream& operator<<(::std::ostream& os, const Figure<ContentsType>& fig) {
//        // Represent in logs or ostream
//        return os << "debug statement for figure class";
//    }

    template <class ContentsType>
    void Figure<ContentsType>::setPlotlyIdFromUrl(std::string url) {

        // Remove any trailing / in case the url is given as, e.g. https://plot.ly/~usr_name/123/
        if (url.back() == '/') {
            url.pop_back();
        }

        // Split the URL into its components. Use ~ as a splitter as well as / to avoid extra op of removing it from user
        std::vector<std::string> url_parts;
        boost::split(url_parts, url, boost::is_any_of("/~"));

        // If the url is given as, e.g. plot.ly/~usr_name/123.embed, remove the .* from the trailing figure id
        std::vector<std::string> trailing_id_parts;
        boost::split(trailing_id_parts, url_parts.back(), boost::is_any_of("."));

        // Assign the Figure properties from the url
        plotly_id = trailing_id_parts[0];
        plotly_usr = url_parts[url_parts.size() - 2];

    }

    template <class ContentsType>
    std::string Figure<ContentsType>::embedUrl() {
    return plotlyUrl() + ".embed";
}

    template <class ContentsType>
    std::string Figure<ContentsType>::pdfUrl() {
        return plotlyUrl() + ".pdf";
    }

    template <class ContentsType>
    void Figure<ContentsType>::plot() {
        // Plot the figure by POSTing its data to the plotly server

        // Get the json data for the figure contents
        std::string body_str = contents.toJson();

        // POST to configuration.url, with configured credentials
        auto r = cpr::Post( cpr::Url{configuration.url},
                            cpr::Body{body_str},
                            cpr::Authentication{configuration.user, configuration.password},
                            cpr::Header{{"Accept", "application/json"}, {"Plotly-Client-Platform", "cpp 0.0.1"}});

        // Remove any trailing / in case the url is given as, e.g. https://plot.ly/~usr_name/123/
        if (r.status_code != 200) {
            std::stringstream msg;
            msg << "Error received from plotly..." <<std::endl;
            msg << "url: " << configuration.url << std::endl;
            msg << "status_code: " << r.status_code << std::endl;
            msg << "content-type: " << r.header["content-type"] << std::endl; // application/json; charset=utf-8
            msg << "text: " << r.text << std::endl;
            ErrorInPlotlyOnlineException e(msg.str());
            throw (e);
        }

        // Expected response...
        auto json = nlohmann::json::parse(r.text);
        std::cout << "Successful response from plotly API... " << std::endl << json.dump(4) << std::endl;

        // TODO Authorization is done, just need to implement the client!
        NotImplementedException e;
        throw (e);

    }

} // end namespace plotly

#endif // CPPLOT_FIGURES_H
