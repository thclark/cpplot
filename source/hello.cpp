#include "hello.h"
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
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "glog/logging.h"


using namespace std;


string hello::greet(void) {
    ostringstream s;
    s << "Hello World" << "!";
    LOG(INFO) << "Output " << s.str()<< " to command line";
    return s.str();

}
hello::hello(){
}
hello::~hello(){
}
