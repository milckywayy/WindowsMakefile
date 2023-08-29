#ifndef TARGET_H_
#define TARGET_H_

#include <string>
#include <vector>


class Target {
private:
    std::string name;
    std::vector<std::string> *dependencies;
    std::vector<std::string> *commands;

public:
    Target(std::string name);
    void addDependence(std::string dependence);
    void addCommand(std::string command);
    std::string getName();
    std::vector<std::string> *getDependencies();
    std::vector<std::string> *getCommands();
    ~Target();
};


#endif