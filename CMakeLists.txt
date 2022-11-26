cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(SFML 2.5.1 COMPONENTS system window network audio REQUIRED)
find_package(ReactPhysics3D  REQUIRED)

include(CMakePackageConfigHelpers)

set(GLM "D:/prog/glm-0.9.9.8")
set(GLEW_H "C:/Program Files (x86)/glew/include")


add_executable(Debug 
    src/main.cpp
    src/Model.cpp 
    src/Window.cpp
    src/Mesh.cpp
    src/Object.cpp
)

add_library(RedEngine
    src/Model.cpp 
    src/Window.cpp
    src/Mesh.cpp
    src/Object.cpp
)

target_link_libraries(Debug PUBLIC 
    OpenGL::GL 
    "C:/Program Files (x86)/glew/lib/glew32.lib" 
    assimp::assimp 
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
    jsoncpp_lib
    ReactPhysics3D::ReactPhysics3D
)

target_link_libraries(RedEngine PUBLIC 
    OpenGL::GL 
    "C:/Program Files (x86)/glew/lib/glew32.lib" 
    assimp::assimp 
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
    jsoncpp_lib
    ReactPhysics3D::ReactPhysics3D
)

set_target_properties(Debug PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(RedEngine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(Debug               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_H}
        ${GLM}
        $<BUILD_INTERFACE:${SFML_INCLUDE_DIR}>
)

target_include_directories(RedEngine               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_H}
        ${GLM}
        $<BUILD_INTERFACE:${SFML_INCLUDE_DIR}>
)

