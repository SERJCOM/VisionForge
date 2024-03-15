#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <filesystem>
#include <string>

namespace vision{


std::ostream& operator << (std::ostream& out, glm::vec3 vec);


void RenderQuad();

std::filesystem::path GetBuildPath();

std::filesystem::path GetCurrentPath();

std::filesystem::path GetShaderPath(std::string file_name);
}