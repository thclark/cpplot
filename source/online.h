/*
 * online.h TODO - this is a collection of snippets from first working with online plotly API.
 * They could be used to form the basis of a plotly client in C++
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

#ifndef CPPLOT_ONLINE_H
#define CPPLOT_ONLINE_H

// Encapsulate plotly config variables. Obtain credentials from the environment upon instantiation.
/* Leaving as a comment - focussing on offline first.
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

// Base class for managing the figure creation process
template <class ContentsType>
class Figure {

private:

    ContentsType contents;

    Config configuration;

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


template <class ContentsType>
Figure<ContentsType>::Figure(ContentsType contents) {

    contents = contents;

    // Get plotly server access configuration and credentials from the environment
    configuration = Config();

}

template <class ContentsType>
std::string Figure<ContentsType>::plotlyUrl() {
    // Returns the URL to this figure on plotly, if the figure is rendered
    if (plotly_usr == "") {
        return "";
    }
    return configuration.url + "/~" + plotly_usr + "/" + plotly_id;
}

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

    NotImplementedException e;
    throw (e);

}

*/
#endif //CPPLOT_ONLINE_H
