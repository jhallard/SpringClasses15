
#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "logstream.h"

using namespace std;

string read_file(const string & fn);

bool write_file(const string & fn, const string & data);

vector<string> split (const string& line, const string& delimiters);

#endif