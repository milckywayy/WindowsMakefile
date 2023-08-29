#ifndef READER_H_
#define READER_H_

#include <vector>
#include <string>
#include "target.h"


std::vector<Target*> *readMakefile(std::string fileName);


#endif