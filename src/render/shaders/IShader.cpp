//
// Created by Twometer on 20/12/2019.
//

#include "IShader.h"
#include "../../util/Loader.h"

void IShader::Initialize(const std::string &name) {
    this->id = Loader::LoadShader(name);
    BindUniforms();
}

void IShader::Bind() {
    glUseProgram(id);
}

void IShader::Unbind() {
    glUseProgram(0);
}

void IShader::LoadMatrix(int loc, glm::mat4 matrix) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

void IShader::LoadVec3(int loc, glm::vec3 vector) {
    glUniform3f(loc, vector.x, vector.y, vector.z);
}

void IShader::LoadVec2(int loc, glm::vec2 vector) {
    glUniform2f(loc, vector.x, vector.y);
}
