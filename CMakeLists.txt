cmake_minimum_required(VERSION 3.14.0)
project(Engine 
    VERSION 0.1.0
    DESCRIPTION "Engine Core For VisionForge Engine"
    LANGUAGES CXX
    )


add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/SFML)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/assimp)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/jsoncpp)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/glm)


set(TGUI_BACKEND SFML_OPENGL3)
add_subdirectory(${CMAKE_SOURCE_DIR}/libraries/TGUI)

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
src/ShadowManager.cpp
src/ShadowComponent.cpp
src/Common.cpp
)



#add_library(VisionForge::VisionForge ALIAS VisionForge)


add_executable(Test 
    test/main.cpp
    ${EngineFiles}
    )

# add_executable(Gui test/GuiTest/main.cpp)
# target_link_libraries(Gui PUBLIC ImGui-SFML::ImGui-SFML sfml-graphics sfml-window OpenGL::GL )
# target_include_directories(Gui PUBLIC ${CMAKE_SOURCE_DIR}/libraries/imgui-sfml ${SFML_INCLUDE_DIRS})

target_link_libraries(Test PUBLIC 
    OpenGL::GL 
    glm
    assimp 
    sfml-graphics sfml-window sfml-audio sfml-network
    jsoncpp_lib
    #ReactPhysics3D::ReactPhysics3D
    ${GLEW_LIBRARIES}
    TGUI::TGUI 
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

