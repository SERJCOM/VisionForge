cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

set(OpenGL_GL_PREFERENCE LEGACY)    

find_package(SFML 3.0.0 COMPONENTS System Window Network Audio REQUIRED)
find_package(assimp REQUIRED)
find_package(OpenGL REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(ReactPhysics3D  REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

include(CMakePackageConfigHelpers)



add_executable(Test 
    test/main.cpp
    src/Model.cpp 
    src/Window.cpp
    src/Mesh.cpp
    src/Object.cpp
    src/Shape.cpp
)

add_library(RedEngine
    src/Model.cpp 
    src/Window.cpp
    src/Mesh.cpp
    src/Object.cpp
    src/Shape.cpp
)



target_link_libraries(Test PUBLIC 
    OpenGL::GL 
    glm::glm
    assimp::assimp 
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
    jsoncpp_lib
    ReactPhysics3D::ReactPhysics3D
    ${GLEW_LIBRARIES}
)




target_link_libraries(RedEngine PUBLIC 
    OpenGL::GL 
    ${GLEW_LIBRARIES}
    assimp::assimp 
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
    jsoncpp_lib
    ReactPhysics3D::ReactPhysics3D

)

set_target_properties(Test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(RedEngine PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(Test               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include

        ${SFML_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}   
)



target_include_directories(RedEngine               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_INCLUDE_DIRS}
        ${GLM}
        ${SFML_INCLUDE_DIR}
        
)