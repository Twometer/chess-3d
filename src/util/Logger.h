//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_LOGGER_H
#define CHESS_3D_LOGGER_H

#include <string>

class Logger {
private:
    static void Print(const std::string &prefix, const std::string &message);

public:
    static void Error(const std::string &message);

    static void Warning(const std::string &message);

    static void Info(const std::string &message);
};


#endif //CHESS_3D_LOGGER_H
