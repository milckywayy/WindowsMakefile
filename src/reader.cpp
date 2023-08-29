#include <iostream>
#include <fstream>
#include <sstream>
#include "reader.h"

using namespace std;


regex TARGET_REGEX(R"(\s*([^#\s]+)\s*:\s*(.*))");
regex COMMAND_REGEX(R"(\s*\t(.+))");
regex EMPTY_LINE_REGEX(R"(^\s*$)");

vector<Target*> *readMakefile(string fileName) {
    vector<Target*> *targets = new vector<Target*>;

    fstream file(fileName);

    if (!file.is_open()) {
        throw invalid_argument("No makefile in current directory");
    }

    string line;
    size_t pos;

    Target *newTarget = NULL;

    while (getline(file, line)) {
        if (line.find('#') != string::npos) {
            line = line.substr(0, line.find('#'));
        }

        if (regex_match(line, EMPTY_LINE_REGEX)) {
            continue;
        }

        pos = 0;

        if (regex_match(line, TARGET_REGEX)) {
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

            newTarget = new Target(line.substr(0, pos++));

            // Read dependencies

            // Eat spaces
            while (line[pos] == ' ' && line[pos] != '\0') {
                pos++;
            }

            if (line[pos] == '\0') {
                // Seems like no dependencies were given
                continue; 
            }

            size_t startPos = pos;
            while (pos < line.size()) {
                if (line[pos] == ' ' || line[pos] == '\0') {
                    newTarget->addDependence(line.substr(startPos, pos - startPos));

                    pos++; 

                    // Eat end characters
                    while ((line[pos] == ' ') && pos < line.size()) {
                        pos++;
                    }

                    startPos = pos;
                }
                else {
                    pos++;
                }
            }
            if (!line.substr(startPos, pos - startPos).empty())
                newTarget->addDependence(line.substr(startPos, pos - startPos));
        }
        else if (regex_match(line, COMMAND_REGEX)) {
            if (newTarget == NULL) {
                delete targets;
                throw invalid_argument("Invalid makefile format");
            }
            else {
                // Add new command
                newTarget->addCommand(line.substr(1, line.size() - 1));
            }
        }
        else {
            // Invalid line
            delete targets;
            throw invalid_argument("Invalid makefile format");
        }
    }

    if (newTarget != NULL) {
        targets->push_back(newTarget);
        newTarget = NULL;
    }

    file.close();

    return targets;
}
