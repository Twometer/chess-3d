//
// Created by Twometer on 18/12/2019.
//

#include "PickEngine.h"
#include "../util/Loader.h"
#include "../model/PieceRegistry.h"


PickEngine::PickEngine(Board *board, Camera *camera) {
    this->board = board;
    this->camera = camera;
    this->fbo = nullptr;

    this->shader = new PickShader();
}

Piece *PickEngine::Pick(int mx, int my) {
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
            model->Draw();
        }


    uint8_t data[3];
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(mx, fbo->GetHeight() - my, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &data);
    glm::vec2 pickPos(data[0], data[1]);

    fbo->Unbind();
    return board->GetPiece(pickPos);
}

void PickEngine::Resize(int width, int height) {
    delete fbo;
    fbo = new Fbo(width, height, DepthBufferType::DEPTH_RBUF);
}
