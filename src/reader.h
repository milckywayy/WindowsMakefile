#ifndef READER_H_
#define READER_H_

#include <vector>
#include <string>
#include <regex>
#include "target.h"


extern std::regex TARGET_REGEX;
extern std::regex COMMAND_REGEX;
extern std::regex EMPTY_LINE_REGEX;

std::vector<Target*> *readMakefile(std::string fileName);


#endif