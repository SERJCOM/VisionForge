#include "VisionForge/EntitySystem/DefaulComponents/ShadowComponent.hpp"
#include <filesystem>

using namespace vision;

using namespace std::filesystem;

void PointShadow::Init(){

}

void PointShadow::Start(){

    auto current_path_ = std::filesystem::current_path() / path("..") / path("shaders");
    current_path_ = current_path_.lexically_normal();
    shadow_shader = Shader(current_path_ / path("shadow.vert"), current_path_ / path("shadow.frag"), current_path_ / path("shadow.geom"));
    

    glGenTextures(1, &depth_map_);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depth_map_);


	for (unsigned int i = 0; i < 6; ++i)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
						width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);  

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  

	aspect = (float)width/(float)height;
	shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, far); 

	UpdateShadowTransform();
}

void PointShadow::UpdateShadowTransform(){
	shadowTransforms.clear();

	shadowTransforms.push_back(shadowProj * glm::lookAt(pos_, pos_ + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
	shadowTransforms.push_back(shadowProj * 
				glm::lookAt(pos_, pos_ + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
	shadowTransforms.push_back(shadowProj * 
				glm::lookAt(pos_, pos_ + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	shadowTransforms.push_back(shadowProj * 
				glm::lookAt(pos_, pos_ + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)));
	shadowTransforms.push_back(shadowProj * 
				glm::lookAt(pos_, pos_ + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)));
	shadowTransforms.push_back(shadowProj * 
				glm::lookAt(pos_, pos_ + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0)));


}