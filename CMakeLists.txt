cmake_minimum_required(VERSION 3.14)
project(chess_3d)

set(CMAKE_CXX_STANDARD 14)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(libs/glm/glm)
add_subdirectory(libs/glfw)
add_subdirectory(libs/json)

add_executable(chess_3d
        ext/glad.cpp
        ext/lodepng.cpp
        src/main.cpp
        src/model/Rule.cpp
        src/model/Board.cpp
        src/model/Piece.cpp
        src/model/Ruleset.cpp
        src/model/PieceRegistry.cpp
        src/model/GameState.cpp
        src/util/Logger.cpp
        src/util/Loader.cpp
        src/util/GlmReader.cpp
        src/util/FontReader.cpp
        src/gl/Mesh.cpp
        src/gl/Model.cpp
        src/gl/Fbo.cpp
        src/render/ChessRenderer.cpp
        src/render/SkyboxRenderer.cpp
        src/render/Camera.cpp
        src/render/Postproc.cpp
        src/render/PickEngine.cpp
        src/render/shaders/IShader.cpp
        src/gui/font/FontRenderer.cpp
        src/gui/GuiRenderer.cpp)

target_include_directories(chess_3d PRIVATE libs/glm libs/glfw/include inc)
target_link_libraries(chess_3d glfw ${GLFW_LIBRARIES} nlohmann_json::nlohmann_json)