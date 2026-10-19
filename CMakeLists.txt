cmake_minimum_required(VERSION 3.20)

project(My3DViewer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(My3DViewer
    main.cpp
    ViewerWindow.cpp
    OpenglRenderSystem.cpp
    GeometryPrimitives.cpp
    glad.c
)

target_include_directories(My3DViewer PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_compile_definitions(My3DViewer PRIVATE
    GLFW_INCLUDE_NONE
)

target_link_libraries(My3DViewer PRIVATE
    glfw
    glm::glm
)
