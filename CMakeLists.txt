cmake_minimum_required(VERSION 3.0.0)
project(Engine VERSION 0.1.0)

add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/SFML)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/assimp)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/jsoncpp)
#add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/glew/build/cmake)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/glm)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(CMakePackageConfigHelpers)



set(EngineFiles 
src/ModelComponent.cpp 
src/Mesh.cpp
src/Object.cpp
src/Skybox.cpp
src/CameraComponent.cpp
src/LightComponent.cpp
src/System.cpp
src/Environment.cpp
src/FrameBuffer.cpp
src/Engine.cpp
src/InputManager.cpp
)

add_executable(Test 
    test/main.cpp
    ${EngineFiles}
)



target_link_libraries(Test PUBLIC 
    OpenGL::GL 
    glm
    assimp 
    sfml-graphics sfml-window sfml-audio sfml-network
    jsoncpp_lib
    #ReactPhysics3D::ReactPhysics3D
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

