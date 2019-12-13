//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_LOADER_H
#define CHESS_3D_LOADER_H

#include <glad/glad.h>
#include <string>

class Loader {

public:
    static std::string LoadFromFile(const std::string &path);

    static GLuint LoadShader(const std::string &name);

};


#endif //CHESS_3D_LOADER_H
