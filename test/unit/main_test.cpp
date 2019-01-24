/*
 * main_test.cpp - The main unit test runner, with a test case printer utility which gives you a stacktrace output.
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

#define BOOST_STACKTRACE_GNU_SOURCE_NOT_REQUIRED

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <boost/stacktrace.hpp>
#include "gtest/gtest.h"
#include "glog/logging.h"


using namespace Eigen;
using namespace google;


class TestCasePrinter : public ::testing::EmptyTestEventListener {

    virtual void OnTestStart(const ::testing::TestInfo& test_info) {
        printf("_____________________________________________________________________________________\n");
        printf("Setting up test %s.%s\n\n", test_info.test_case_name(), test_info.name());
    }

    const char* PrintStackTrace(void) {
        printf("Failed with stack trace:\n\n");
        // TODO implement stack trace printer
        // See:
        //  https://github.com/google/googletest/issues/1140
        //  http://boostorg.github.io/stacktrace/stacktrace/getting_started.html#stacktrace.getting_started.handle_terminates_aborts_and_seg
        std::cout << boost::stacktrace::stacktrace();
        return "Failed";
    }

    // Called after a failed assertion or a SUCCEED() invocation
    virtual void OnTestPartResult(const ::testing::TestPartResult& test_part_result) {
        printf("%s in %s:%d\n",
               test_part_result.failed() ? PrintStackTrace() : "Success",
               test_part_result.file_name(),
               test_part_result.line_number());
    }

    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
        printf("Torn down test %s.%s\n", test_info.test_case_name(), test_info.name());
        printf("_____________________________________________________________________________________\n\n\n");
    }

};


int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    // Some code being tested may support logging, so we need to initialise the google logger here where we have the
    // executable name in argv[0]
    google::InitGoogleLogging(argv[0]);

    // Get hold of the event listener list
    ::testing::TestEventListeners& listeners = ::testing::UnitTest::GetInstance()->listeners();

    // Removing the default result printer prevents CLion from picking up the unit tests, so the custom printer is
    // added, rather than simply replacing the default
    //	delete listeners.Release(listeners.default_result_printer());

    // Adds a listener for printing outputs (including e.g. stack traces)
    listeners.Append(new TestCasePrinter);

    int a = RUN_ALL_TESTS();

    return a;

}
