#include <iostream>
#include "target.h"

using namespace std;


Target::Target(string name) {
    this->dependencies = new vector<string>;
    this->commands = new vector<string>;
    this->name = name;
}

void Target::addDependence(string dependence) {
    dependencies->push_back(dependence);
}

void Target::addCommand(string command) {
    commands->push_back(command);
}

string Target::getName() {
    return name;
}

vector<string> *Target::getDependencies() {
    return dependencies;
}

vector<string> *Target::getCommands() {
    return commands;
}

void Target::print() {
    cout << "Name: " << name << endl;
    
    cout << "Dependecies: ";
    for (string s : *dependencies) {
        cout << s << " ";
    }  
    cout << endl;

    cout << "Commands: ";
    for (string s : *commands) {
        cout << s << endl;
    }  
    cout << endl;
}

Target::~Target() {
    delete dependencies;
    delete commands;
}

