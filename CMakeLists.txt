cmake_minimum_required(VERSION 3.14)
project(chess_3d)

set(CMAKE_CXX_STANDARD 14)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(libs/glm/glm)
add_subdirectory(libs/glfw)
add_subdirectory(libs/json)

add_executable(chess_3d ext/glad.c src/main.cpp src/model/Rule.cpp src/model/Rule.h src/model/Team.h src/model/Board.cpp src/model/Board.h src/model/MoveResult.h src/model/Piece.cpp src/model/Piece.h src/model/Ruleset.cpp src/model/Ruleset.h src/model/PieceType.h src/util/Logger.cpp src/util/Logger.h src/util/Loader.cpp src/util/Loader.h src/gl/Mesh.cpp src/gl/Mesh.h src/gl/Model.cpp src/gl/Model.h src/util/Buffer.h src/util/StlReader.cpp)
target_include_directories(chess_3d PRIVATE libs/glm libs/glfw/include inc)
target_link_libraries(chess_3d glfw ${GLFW_LIBRARIES} nlohmann_json::nlohmann_json)