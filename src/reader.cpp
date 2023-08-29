#include <iostream>
#include <fstream>
#include <sstream>
#include "reader.h"

using namespace std;


vector<Target*> *readMakefile(string fileName) {
    vector<Target*> *targets = new vector<Target*>;

    fstream file(fileName);

    if (!file.is_open()) {
        throw invalid_argument("No makefile in current directory");
    }

    string line;
    string target;
    string dependece;
    string command;
    size_t pos;

    Target *newTarget = NULL;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        pos = 0;

        if (line[0] != '\t') {
            // Close previous target
            if (newTarget != NULL) {
                targets->push_back(newTarget);
                newTarget = NULL;
            }

            // Read new target

            while (line[pos] != ':' && line[pos] != '\0') {
                pos++;
            }

            if (line[pos] == '\0') {
                throw invalid_argument("Invalid makefile format");
            }

            target = line.substr(0, pos++);
            newTarget = new Target(target);

            // Read dependencies

            // Eat spaces
            while (line[pos] == ' ' && line[pos] != '\0') {
                pos++;
            }

            if (line[pos] == '\0') {
                delete newTarget;
                throw invalid_argument("Invalid makefile format");
            }

            size_t startPos = pos;
            while (pos <= line.size()) {
                if (line[pos] == ' ' || line[pos] == '\0') {
                    newTarget->addDependence(line.substr(startPos, pos - startPos));

                    pos++;

                    // Eat end characters
                    while ((line[pos] == ' ' || line[pos] == '\0') && pos <= line.size()) {
                        pos++;
                    }

                    startPos = pos;
                }
                else {
                    pos++;
                }
            }

        }
        else if (line[0] == '\t') {
            if (newTarget == NULL) {
                throw invalid_argument("Invalid makefile format");
            }
            else {
                newTarget->addCommand(line);
            }
        }
    }

    if (newTarget != NULL) {
        targets->push_back(newTarget);
        newTarget = NULL;
    }

    file.close();

    for (Target *t : *targets) {
        t->print();
    }

    delete targets;

    return targets;
}
