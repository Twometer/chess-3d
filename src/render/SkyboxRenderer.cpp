//
// Created by Twometer on 22/12/2019.
//

#include "SkyboxRenderer.h"
#include "../util/Loader.h"

std::vector<std::string> SkyboxRenderer::TEXTURE_FILES = {"posx", "negx", "posy", "negy", "posz", "negz"};

SkyboxRenderer::SkyboxRenderer() {
    model = Loader::LoadModel("skybox.glm");
    texture = Loader::LoadCubemap(TEXTURE_FILES);
    shader = new SkyboxShader();
}

void SkyboxRenderer::Render(Camera *camera) {
    shader->Bind();
    shader->SetProjectionMatrtix(camera->GetProjectionMatrix());
    shader->SetViewMatrix(camera->GetViewMatrix());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    model->Draw();

    shader->Unbind();
}

GLuint SkyboxRenderer::GetTexture() {
    return texture;
}

