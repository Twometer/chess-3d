//
// Created by Twometer on 18/12/2019.
//

#include "PickEngine.h"
#include "../util/Loader.h"
#include "../model/PieceRegistry.h"
#include "ChessRenderer.h"


PickEngine::PickEngine(Board *board, Camera *camera) {
    this->board = board;
    this->camera = camera;
    this->fbo = nullptr;

    this->shader = new PickShader();
}

Piece *PickEngine::PickPiece(int mx, int my) {
    fbo->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->Bind();
    shader->SetMvpMatrix(camera->GetMatrix());

    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++) {
            glm::vec2 pos(x, y);
            Piece *piece = board->GetPiece(pos);
            if (piece == nullptr) continue;

            shader->SetPosition(pos);

            Model *model = PieceRegistry::GetModel(piece->type);
            model->Render();
        }


    uint8_t data[3];
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(mx, fbo->GetHeight() - my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &data);
    glm::vec2 pickPos(data[0], data[1]);

    fbo->Unbind();
    return board->GetPiece(pickPos);
}

PickResult PickEngine::Pick(int mx, int my) {
    Piece *piece = PickPiece(mx, my);
    if (piece != nullptr)
        return {PIECE, glm::vec2(), piece};

    glm::vec3 deviceCoordinates = glm::vec3(
            (2.0f * mx) / ChessRenderer::GetViewportSize().x - 1.0f,
            1.0f - (2.0f * my) / ChessRenderer::GetViewportSize().y,
            1.0f
    );
    glm::vec4 ray_clip = glm::vec4(deviceCoordinates.x, deviceCoordinates.y, -1.0, 1.0);
    glm::vec4 ray_eye = glm::inverse(camera->GetProjectionMatrix()) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
    glm::vec4 ray_world = glm::inverse(camera->GetViewMatrix()) * ray_eye;
    glm::vec3 ray = glm::normalize(glm::vec3(ray_world.x, ray_world.y, ray_world.z));

    glm::vec3 pos = camera->GetEyePosition();

    int attempts = 0;
    while (pos.y > 0) {
        pos += ray;
        attempts++;
        if (attempts > 100)
            return {MISS, glm::vec2(), nullptr};
    }

    return {BOARD, glm::vec2(floor(pos.x / 2.0f), floor(pos.z / 2.0f)), nullptr};
}

void PickEngine::Resize(int width, int height) {
    delete fbo;
    fbo = new Fbo(width, height, DepthBufferType::DEPTH_RBUF);
}


