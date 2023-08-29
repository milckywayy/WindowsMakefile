#include <iostream>
#include <string>
#include <vector>
#include "target.h"
#include "reader.h"


using namespace std;


int main(int argc, char **argv) {
    vector<string> targets;

    if (argc == 1) {
        try {
            readMakefile("makefile");
        }
        catch (exception &e) {
            cerr << e.what() << endl;
        }
    }
    else {
        for (int i = 1; i < argc; i++) {
            targets.push_back(argv[i]);
        }

        
    }

    /*
    for (int i = 0; i < targets.size(); i++) {
        cout << targets[i] << endl; 
    }
    */
    
    return 0;
}