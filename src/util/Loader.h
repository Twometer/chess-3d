//
// Created by Twometer on 13/12/2019.
//

#ifndef CHESS_3D_LOADER_H
#define CHESS_3D_LOADER_H

#include <glad/glad.h>
#include <string>

#include "../gl/Model.h"

struct Image {
    uint8_t *ptr;
    unsigned int size;
    unsigned int width;
    unsigned int height;
};

class Loader {
private:
    static Image LoadImage(const std::string &path);

    static void CheckShader(const std::string &name, GLuint shader);

public:
    static std::string ReadAllText(const std::string &path);

    static uint8_t *ReadAllBytes(const std::string &path);

    static GLuint LoadShader(const std::string &name);

    static GLuint LoadShader(const std::string &vname, const std::string &fname);

    static Model *LoadModel(const std::string &name);

    static GLuint LoadCubemap(const std::vector<std::string> &names);
};


#endif //CHESS_3D_LOADER_H
