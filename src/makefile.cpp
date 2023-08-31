#include <iostream>
#include <cstdlib>
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

bool Makefile::isTargetSelected(Target *target) {
    for (string selected : *selectedTargets) {
        if (selected == target->getName()) {
            return true;
        }
    }

    return false;
}

void Makefile::runTarget(Target *target) {
    time_t targetModTime;
    bool upToDate = true;

    // Check if target is up to date
    try {
        targetModTime = getFileModTime(target->getName());
        for (string dependency : *(target->getDependencies())) {
            if (targetModTime < getFileModTime(dependency)) {
                upToDate = false;
            }
        }
    }
    catch (invalid_argument &e) {
        upToDate = false;
    }

    if (upToDate) { 
        throw runtime_error("Target '" + target->getName() + "' is up to date");
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

    // Run commands
    for (string command : *(target->getCommands())) {
        // replacing " with ' in order to work with powershell
        for (int i = 0; i < command.size(); i++) {
            if (command[i] == '"') {
                command[i] = '\'';
            }
        }

        if (system(("powershell \"" + command + "\"").c_str()) == 0) {
            cout << command << endl;
        }
        else {
            cout << "Execution failed for: '" << command << "'" << endl;
        }
    }
}

void Makefile::run() {
    if (selectedTargets == NULL) {
        try {
            runTarget(targets->at(0));
        }
        catch (const runtime_error &e) {
            cout << e.what() << endl;  
        }
        catch (const exception &e) {
            cerr << e.what() << endl;
        }
    }
    else {
        for (Target *target : *targets) {
            if (isTargetSelected(target)) {
                try {
                    runTarget(target);
                }
                catch (const runtime_error &e) { 
                    cout << e.what() << endl;  
                }
                catch (const exception &e) {
                    cerr << e.what() << endl;
                }
            }
        }
    }
}

Makefile::~Makefile() {
    for (Target* t : *targets) {
        delete t;
    }

    delete targets;
}
