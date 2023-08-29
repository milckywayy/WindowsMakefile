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
        cout << line << endl; 
        
        if (line.empty()) {
            continue;
        }

        pos = 0;

        if (line[0] != '\t') {
            // Read new target

            while (line[pos] != ':' && line[pos] != '\0') {
                pos++;
            }

            if (line[pos] == '\0') {
                throw invalid_argument("Invalid makefile format");
            }

            target = line.substr(0, pos++);
            newTarget = new Target(target);

            cout << "Target: " << target << endl;

            // Read dependencies

            // Eat spaces
            while (line[pos] == ' ' && line[pos] != '\0') {
                pos++;
            }

            if (line[pos] == '\0') {
                throw invalid_argument("Invalid makefile format");
            }

            size_t startPos = pos;
            while (pos <= line.size()) {
                if (line[pos] == ' ' || line[pos] == '\0') {
                    cout << "Dependence: " << line.substr(startPos, pos - startPos) << endl;
                    newTarget->addDependence(line.substr(startPos, pos));

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
            // Reading new command
        }

    }

    file.close();

    delete targets;

    return targets;
}
