//
// Created by Twometer on 20/12/2019.
//

#ifndef CHESS_3D_ISHADER_H
#define CHESS_3D_ISHADER_H

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class IShader {
protected:
    GLuint id;

    void Initialize(const std::string &name);

    void Initialize(const std::string &vname, const std::string &fname);

    virtual void BindUniforms() = 0;

    void LoadMatrix(int loc, glm::mat4 matrix);

    void LoadVec2(int loc, glm::vec2 vector);

    void LoadVec3(int loc, glm::vec3 vector);

    void LoadVec4(int loc, glm::vec4 vector);

public:

    void Bind();

    void Unbind();

};


#endif //CHESS_3D_ISHADER_H
