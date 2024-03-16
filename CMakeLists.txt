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
imgui/imconfig.h
imgui/imgui_demo.cpp
imgui/imgui_draw.cpp
imgui/imgui_impl_glfw.cpp
imgui/imgui_impl_glfw.h
imgui/imgui_impl_opengl3.cpp
imgui/imgui_impl_opengl3.h
imgui/imgui_internal.h
imgui/imgui_widgets.cpp
imgui/imgui.cpp
imgui/imgui.h
imgui/imstb_rectpack.h
imgui/imstb_textedit.h
imgui/imstb_truetype.h
imgui/imgui_tables.cpp
)

option(MYLIB_INSTALL "Generate target for installing mylib" ${is_top_level})
include(cmake/utils.cmake)
include(GNUInstallDirs)


set_if_undefined(VISIONFORGE_INSTALL_CMAKEDIR 
    "${CMAKE_INSTALL_LIBDIR}/cmake/VisionForge-${PROJECT_VERSION}" CACHE STRING
    "Install path for VisionForge package-related CMake files")

message(STATUS ${CMAKE_INSTALL_LIBDIR})

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

target_include_directories(Test               
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${GLEW_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/libraries
        ${CMAKE_SOURCE_DIR}/test
        ${SFML_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/imgui
)

# if(MYLIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)

include(CMakePackageConfigHelpers)

# if(MYLIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)

configure_package_config_file(cmake/Config.cmake.in visionforge-config.cmake
    INSTALL_DESTINATION "${VISIONFORGE_INSTALL_CMAKEDIR}")

# message()

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


# endif()

# endif()