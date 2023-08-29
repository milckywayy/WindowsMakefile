#include <iostream>
#include <ctime>
#include <sys/stat.h>
#include "utils.h"

using namespace std;


time_t getFileModTime(string fileName) {
    struct stat fileInfo;

    if (stat(fileName.c_str(), &fileInfo) == 0) {
        time_t mod_time = fileInfo.st_mtime;
        return mod_time;
    }
    else {
        throw new invalid_argument("File " + fileName + " does not exist");
    }
}