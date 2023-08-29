#include <iostream>
#include "makefile.h"
#include "utils.h"

using namespace std;


Makefile::Makefile(vector<Target*> *targets) {
    this->targets = targets;
    this->selectedTargets = NULL;
}

Makefile::Makefile(vector<Target*> *targets, vector<string> *selectedTargets) {
    this->targets = targets;
    this->selectedTargets = selectedTargets;
}

bool Makefile::isTarget(string dependency) {
    for (Target *t : *targets) {
        if (t->getName() == dependency) {
            return true;
        }
    }

    return false;
}

int Makefile::runTarget(Target *target) {
    time_t targetModTime;
    bool upToDate = true;

    // Check if target is up to date
    targetModTime = getFileModTime(target->getName());
    for (string dependency : *(target->getDependencies())) {
        if (targetModTime < getFileModTime(dependency)) {
            upToDate = false;
        }
    }

    if (upToDate) {
        // Target is up to date - no need to do anything
        return 1;
    }

    // Update dependecy targets
    for (string dependency : *(target->getDependencies())) {
        if (isTarget(dependency)) {
            for (Target *t : *targets) {
                if (t->getName() == dependency) {
                    runTarget(t);
                }
            }
        }
    }

    // Run 
    for (string command : *(target->getCommands())) {
        cout << "RUN!! " << command << endl;
    }

    return 0;

}

int Makefile::run() {
    if (selectedTargets == NULL) {
        runTarget(targets->at(0));
    }
    else {
        // TODO Run selected
    }

    return 0;
}

Makefile::~Makefile() {
    for (Target* t : *targets) {
        delete t;
    }

    delete targets;
}
