#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model/Board.h"
#include "model/Ruleset.h"
#include "util/Logger.h"

using namespace std;

int main() {
    Logger::Info("Loading ruleset...");
    Ruleset *ruleset = Ruleset::Load("assets/rules.json");
    auto *board = new Board(ruleset);
    board->Initialize();

    if (!glfwInit()) {
        Logger::Error("Failed to initialize GLFW");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1000, 700, "3D Chess", nullptr, nullptr);
    if (!window) {
        Logger::Error("Failed to create GLFW window");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        Logger::Error("Failed to initialize OpenGL");
        glfwTerminate();
        return 1;
    }

    Logger::Info("Successfully initialized");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}