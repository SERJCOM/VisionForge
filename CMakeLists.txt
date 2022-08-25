cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)
find_package(jsoncpp REQUIRED)

set(GLM "D:/prog/glm-0.9.9.8")

set(GLEW_H "C:/Program Files (x86)/glew/include")

set(SFML_L ${CMAKE_SOURCE_DIR}/add_libraries/SFML-2.5.1)


add_executable(Engine 
    src/main.cpp
    src/Engine.cpp 
    src/Model.cpp 
    src/Window.cpp
)

message(STATUS  ${CMAKE_SOURCE_DIR} )

target_link_libraries(Engine PUBLIC 
    "D:/prog/reactphysics3d/build/Debug/reactphysics3d.lib" 
    OpenGL::GL "C:/Program Files (x86)/glew/lib/glew32.lib" 
    assimp::assimp 
    ${SFML_L}/lib/sfml-graphics-d.lib 
    ${SFML_L}/lib/sfml-window-d.lib 
    ${SFML_L}/lib/sfml-system-d.lib 
    ${SFML_L}/lib/sfml-audio-d.lib 
    ${SFML_L}/lib/sfml-network-d.lib 
    jsoncpp_lib
)

set_target_properties(Engine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(Engine               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_H}
        ${GLM}
        ${SFML_L}/include
        "D:/prog/reactphysics3d/include"
)


