cmake_minimum_required(VERSION 3.14.0)
project(Engine 
    VERSION 0.1.0
    DESCRIPTION "Engine Core For VisionForge Engine"
    LANGUAGES CXX
    )


find_package(SFML 3.0.0 COMPONENTS System Window Network Audio REQUIRED )

find_package(assimp REQUIRED)
find_package(jsoncpp REQUIRED)
set(TGUI_BACKEND SFML_OPENGL3)
find_package(TGUI 1 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

find_package(glfw3  REQUIRED)


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
src/Shader.cpp
src/Blur.cpp
src/Sun.cpp
src/PostProcessing.cpp
)

set(ImGuiFiles
include/VisionForge/imgui/imconfig.h
include/VisionForge/imgui/imgui_demo.cpp
include/VisionForge/imgui/imgui_draw.cpp
include/VisionForge/imgui/imgui_impl_glfw.cpp
include/VisionForge/imgui/imgui_impl_glfw.h
include/VisionForge/imgui/imgui_impl_opengl3.cpp
include/VisionForge/imgui/imgui_impl_opengl3.h
include/VisionForge/imgui/imgui_internal.h
include/VisionForge/imgui/imgui_widgets.cpp
include/VisionForge/imgui/imgui.cpp
include/VisionForge/imgui/imgui.h
include/VisionForge/imgui/imstb_rectpack.h
include/VisionForge/imgui/imstb_textedit.h
include/VisionForge/imgui/imstb_truetype.h
include/VisionForge/imgui/imgui_tables.cpp
)

option(MYLIB_INSTALL "Generate target for installing mylib" ${is_top_level})
include(cmake/utils.cmake)
include(GNUInstallDirs)


set_if_undefined(VISIONFORGE_INSTALL_CMAKEDIR 
    "${CMAKE_INSTALL_LIBDIR}/cmake/VisionForge-${PROJECT_VERSION}" CACHE STRING
    "Install path for VisionForge package-related CMake files")

message(STATUS ${CMAKE_INSTALL_LIBDIR})

if(ENGINE_RELEASE)
	add_definitions("-DCURRENT_DIRECTORY=\"${CMAKE_INSTALL_PREFIX}/include/VisionForge\"")
    add_definitions("-DSHADERS_DIRECTORY=\"${CMAKE_INSTALL_PREFIX}/share/VisionForge/shaders\"")
    add_definitions("-DGAMESDK_DIRECTORY=\"${CMAKE_INSTALL_PREFIX}/share/VisionForge/game_sdk\"")
else()
	add_definitions("-DCURRENT_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}/\"")
    add_definitions("-DSHADERS_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}/shaders\"")
    add_definitions("-DGAMESDK_DIRECTORY=\"${CMAKE_CURRENT_SOURCE_DIR}/game_sdk\"")
endif()

message(${CMAKE_INSTALL_PREFIX})

add_library(VisionForge STATIC ${EngineFiles} ${ImGuiFiles})

target_link_libraries(VisionForge PUBLIC 
    OpenGL::GL 
    glm::glm
    SFML::Graphics SFML::Audio SFML::Network
    jsoncpp_lib
    assimp::assimp
    ${GLEW_LIBRARIES}
    spdlog::spdlog
    glfw
)


target_include_directories(VisionForge PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${GLEW_INCLUDE_DIRS}>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/libraries>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/test>
    $<BUILD_INTERFACE:${SFML_INCLUDE_DIRS}>
    
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/imgui>
)

target_link_directories(VisionForge PUBLIC 
    ${GLEW_INCLUDE_DIRS}
    ${SFML_INCLUDE_DIRS}
)

add_executable(Test 
    test/main.cpp
    ${EngineFiles}
    ${ImGuiFiles}
)

target_include_directories(Test               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/libraries
        ${CMAKE_SOURCE_DIR}/test
        ${SFML_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/imgui
)


target_link_libraries(Test PUBLIC 
    OpenGL::GL 
    glm::glm
    SFML::Graphics SFML::Audio SFML::Network
    jsoncpp_lib
    assimp::assimp
    ${GLEW_LIBRARIES}
    spdlog::spdlog
    glfw
)




set_target_properties(Test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


include(CMakePackageConfigHelpers)

configure_package_config_file(cmake/Config.cmake.in visionforge-config.cmake
    INSTALL_DESTINATION "${VISIONFORGE_INSTALL_CMAKEDIR}")


write_basic_package_version_file(visionforge-config-version.cmake
    COMPATIBILITY SameMajorVersion)

install(TARGETS VisionForge
  	EXPORT VisionForgeExport
  	LIBRARY DESTINATION lib
	INCLUDES DESTINATION include/VisionForge
)

install(EXPORT VisionForgeExport
	FILE VisionForgeTargets.cmake
	NAMESPACE VisionForge::
  	DESTINATION "${VISIONFORGE_INSTALL_CMAKEDIR}"
)


install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/visionforge-config.cmake
	DESTINATION "${VISIONFORGE_INSTALL_CMAKEDIR}"
)


install(DIRECTORY "include/VisionForge"
DESTINATION include 

USE_SOURCE_PERMISSIONS
)

install(FILES ${ImGuiFiles}
DESTINATION include/VisionForge/imgui
)

install(DIRECTORY "game_sdk" 
DESTINATION "share/VisionForge"
USE_SOURCE_PERMISSIONS
)

install(DIRECTORY "shaders" 
DESTINATION "share/VisionForge"
USE_SOURCE_PERMISSIONS
)


