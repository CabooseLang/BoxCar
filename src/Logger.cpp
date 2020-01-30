#include "Logger.hpp"

#include <ctime>
#include <iostream>
#include <sstream>

void padTo(std::string str, const size_t num, const char paddingChar = ' ') {
    if(num > str.size()) str.insert(0, num - str.size(), paddingChar);
}

void BoxCar::Logging::Logger::err(std::string message) {
    internalLog(BoxCar::Logging::LogSeverity::ERR, message);
}

void BoxCar::Logging::Logger::inf(std::string message) {
    internalLog(BoxCar::Logging::LogSeverity::INF, message);
}

void BoxCar::Logging::Logger::internalLog(BoxCar::Logging::LogSeverity severity,
                                     const std::string& message) {
    std::string severityString;

    switch (severity) {
        case BoxCar::Logging::LogSeverity::FTL:
            severityString = "FTL";
            break;
        case BoxCar::Logging::LogSeverity::ERR:
            severityString = "ERR";
            break;
        case BoxCar::Logging::LogSeverity::WRN:
            severityString = "WRN";
            break;
        case BoxCar::Logging::LogSeverity::INF:
            severityString = "INF";
            break;
        case BoxCar::Logging::LogSeverity::DBG:
            severityString = "DBG";
            break;
    }

    std::time_t t = std::time(nullptr);
    std::tm* timePtr = localtime(&t);

    // Format Hours
    std::stringstream hourStream;
    hourStream << timePtr->tm_hour;
    std::string hour = hourStream.str();
    padTo(hour, 2, '0');

    // Format Minutes
    std::stringstream minuteStream;
    minuteStream << timePtr->tm_min;
    std::string minute = minuteStream.str();
    padTo(minute, 2, '0');

    // Format Seconds
    std::stringstream secondStream;
    secondStream << timePtr->tm_sec;
    std::string second = secondStream.str();
    padTo(second, 2, '0');

    std::cout << "[" << hour << ":" << minute << ":" << second << " BoxCar " << severityString << "] " << message << std::endl;
}