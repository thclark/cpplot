/*
 * hello.cpp Hello World
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
#ifndef hello_h
#define hello_h
#include <stdlib.h>
#include <stdio.h>
//#include <unistd.h>
#include <stdbool.h>
//#include "matio.h"
#include <iostream>
#include <sstream>
#include "glog/logging.h"


//#include <Eigen/Core>
//#include <unsupported/Eigen/FFT>
using namespace std;

class hello
{
public:
    static string greet(void);
    hello(void);
    ~hello(void);
};

#endif /* hello_h*/
