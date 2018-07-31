/*
 * exceptions.h Customised exceptions for appropriate and fine grained error handling
 *
 * Author:              Tom Clark  (thclark@github)
 *
 * Copyright (c) 2017-8 T Clark. All Rights Reserved.
 *
 */

#ifndef CPPLOT_EXCEPTIONS_H
#define CPPLOT_EXCEPTIONS_H

#include <exception>


struct NotImplementedException : public std::exception {
    std::string message = "Not yet implemented";
    const char * what () const throw () {
        return message.c_str();
    }
};

struct InvalidOrMissingPlotlyCredentialsException : public std::exception {
    std::string message = "Invalid or missing plotly credentials. Try setting the environment variables PLOTLY_USERNAME and PLOTLY_PASSWORD.";
    const char * what () const throw () {
        return message.c_str();
    }
};

struct ErrorInPlotlyOnlineException : public std::exception {
    std::string message = "";
    const char * what () const throw () {
        return message.c_str();
    }
    ErrorInPlotlyOnlineException() {
        message = "Error in plotly online";
    }
    ErrorInPlotlyOnlineException(const std::string msg) {
        message = msg;
    }
};

#endif // CPPLOT_EXCEPTIONS_H
