#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model/Board.h"
#include "model/Ruleset.h"
#include "util/Logger.h"
#include "util/Loader.h"
#include "render/ChessRenderer.h"

using namespace std;

int main() {
    Logger::Info("Initializing rendering context...");
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

    ChessRenderer renderer(window);
    renderer.Initialize();
    renderer.OnViewportSizeChanged(glm::vec2(1000, 700));

    Logger::Info("Successfully initialized");

    while (!glfwWindowShouldClose(window)) {
        renderer.RenderFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}