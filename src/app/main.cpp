// Standard Libraries
#include "../Package.hpp"
#include <deque>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc > 1) {
        std::deque<std::string> args(argv + 1, argv + argc);
        std::string command = args.front();
        args.pop_front();

        if (command == "install") {
            BoxCar::Package package;
            package.readFromJsonFile("./boxcar.json");
            package.installAllDependencies();
        }
    } else std::cerr << "You must supply a command for BoxCar to perform." << std::endl;
}