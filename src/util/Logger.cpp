//
// Created by Twometer on 13/12/2019.
//

#include "Logger.h"

#include <iostream>

void Logger::Print(const std::string &prefix, const std::string &message) {
    std::cout << "[" << prefix << "] " << message << std::endl;
}

void Logger::Error(const std::string &message) {
    Print("ERROR", message);
}

void Logger::Warning(const std::string &message) {
    Print("WARN", message);
}

void Logger::Info(const std::string &message) {
    Print("INFO", message);
}
