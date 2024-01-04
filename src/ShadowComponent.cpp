#include "VisionForge/EntitySystem/DefaulComponents/ShadowComponent.hpp"

using namespace vision;

void PointShadow::Start(){
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