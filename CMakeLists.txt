cmake_minimum_required(VERSION 3.15)
project(chess_3d)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(glm)
include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(chess_3d ext/glad.c src/main.cpp)

# Asset copying
macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach (templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if (NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    @ONLY)
        endif (NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach (templateFile)
endmacro(configure_files)
configure_files(assets assets)