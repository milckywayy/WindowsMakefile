#include "makefile.h"

using namespace std;


Makefile::Makefile(vector<Target*> *targets) {
    this->targets = targets;
    this->selectedTargets = NULL;
}

Makefile::Makefile(vector<Target*> *targets, vector<string> *selectedTargets) {
    this->targets = targets;
    this->selectedTargets = selectedTargets;
}

void Makefile::run() {
    if (selectedTargets) {
        // TODO Run default
    }
    else {
        // TODO Run selected
    }
}

Makefile::~Makefile() {
    for (Target* t : *targets) {
        delete t;
    }

    delete targets;
}
