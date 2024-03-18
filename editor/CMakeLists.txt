cmake_minimum_required(VERSION 3.25)
project(editor)

find_package(SFML 3.0.0 COMPONENTS System Window Network Audio REQUIRED )
find_package(assimp REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(VisionForge REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)
find_package(glfw3  REQUIRED)

add_definitions("-DCURRENT_DIRECTORY=\"${CMAKE_INSTALL_PREFIX}/include/VisionForge\"")
add_definitions("-DSHADERS_DIRECTORY=\"${CMAKE_INSTALL_PREFIX}/share/VisionForge/shaders\"")
add_definitions("-DGAMESDK_DIRECTORY=\"${CMAKE_INSTALL_PREFIX}/share/VisionForge/game_sdk\"")

add_executable(Editor src/editor.cpp)

target_include_directories(Editor PUBLIC 
${CMAKE_SOURCE_DIR}/include
${GLEW_INCLUDE_DIRS}
${SFML_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/imgui
)

target_link_directories(Editor PUBLIC 
    ${GLEW_INCLUDE_DIRS}
    ${SFML_INCLUDE_DIRS}
)

message(${GLEW_LIBRARIES})

target_link_libraries(Editor PUBLIC 
VisionForge
OpenGL::GL 
glm::glm
SFML::Graphics SFML::Audio SFML::Network
jsoncpp_lib
assimp::assimp
${GLEW_LIBRARIES}
spdlog::spdlog
glfw

)