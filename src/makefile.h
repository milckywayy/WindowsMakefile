#ifndef MAKEFILE_H_
#define MAKEFILE_H_

#include <vector>
#include <string>
#include "target.h"


class Makefile {
private:
    std::vector<Target*> *targets;
    std::vector<std::string> *selectedTargets;

public:
    Makefile(std::vector<Target*> *targets);
    Makefile(std::vector<Target*> *targets, std::vector<std::string> *selectedTargets);
    bool isTarget(std::string dependency);
    bool isTargetSelected(Target *target);
    void runTarget(Target *target);
    void run();
    ~Makefile();
};


#endif