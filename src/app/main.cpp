// Standard Libraries
#include "../Logger.hpp"
#include "../Package.hpp"
#include <deque>
#include <iostream>
#include <string>

int
main(int argc, char** argv) {
    if (argc > 1) {
        std::deque<std::string> args(argv + 1, argv + argc);
        std::string command = args.front();
        args.pop_front();

        if (command == "install") {
            BoxCar::Packaging::Package package;
            package.readFromJsonFile("./boxcar.json");

            BoxCar::Packaging::PackageValidity validity = package.validate();

            if (validity.valid)
                package.installAllDependencies();
            else {
                BoxCar::Logging::Logger::err(validity.error);
                return 1;
            }
        }
    } else {
        BoxCar::Logging::Logger::err(
          "You must supply a command for BoxCar to perform.");
        return 1;
    }
}