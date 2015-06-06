
#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>


#include "logstream.h"

using namespace std;

string read_file(const string & fn);

bool write_file(const string & fn, const string & data);

#endif