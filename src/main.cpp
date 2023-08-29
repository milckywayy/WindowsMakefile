#include <iostream>
#include <string>
#include <vector>
#include "target.h"
#include "reader.h"
#include "makefile.h"


using namespace std;


int main(int argc, char **argv) {
    Makefile *makefile;
    vector<Target*> *targets;
    vector<string> selectedTargets;

    try {
        targets = readMakefile("makefile");
    }
    catch (exception &e) {
        cerr << e.what() << endl;
        return 1;
    }

    if (argc == 1) {
        makefile = new Makefile(targets);
    }
    else {
        for (int i = 1; i < argc; i++) {
            selectedTargets.push_back(argv[i]);
        }

        makefile = new Makefile(targets, &selectedTargets);
    }

    try {
        makefile->run();
    }
    catch (exception &e) {
        delete makefile;
        cerr << e.what() << endl;
        return 1;
    }

    delete makefile;
    
    return 0;
}