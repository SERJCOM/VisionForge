cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

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
    src/Mesh.cpp
    src/Object.cpp
    src/Skybox.cpp
    src/CameraComponent.cpp
    src/LightComponent.cpp
    src/System.cpp
    src/Environment.cpp
    src/FrameBuffer.cpp
    src/Engine.cpp
)



target_link_libraries(Test PUBLIC 
    OpenGL::GL 
    glm::glm
    assimp::assimp 
    SFML::Graphics SFML::Window SFML::Audio SFML::Network
    jsoncpp_lib
    ReactPhysics3D::ReactPhysics3D
    ${GLEW_LIBRARIES}
)



set_target_properties(Test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_include_directories(Test               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/libraries
        ${CMAKE_SOURCE_DIR}/test
        ${SFML_INCLUDE_DIRS}
)

