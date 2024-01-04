#pragma once 

#include "VisionForge/EntitySystem/Components/ShadowInterface.hpp"
#include "VisionForge/System/Shader.hpp"

namespace vision{

class PointShadow : public IShadow{
public:

    PointShadow(){
        
    }

    void Prepare() override{
        glViewport(0, 0, width, height);
        glClear(GL_DEPTH_BUFFER_BIT);

        shadow.use();

        for(int i = 0; i < shadowTransforms.size(); i++){
            shadow.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
        }

        shadow.setFloat("far_plane", far);
        shadow.setVec3("lightPos", pos_);

    }

    void Update() override{

    }

    void Start() override;

private:

    void UpdateShadowTransform(); 

    Shader shadow;
    std::vector<glm::mat4> shadowTransforms;
    float aspect;
    glm::mat4 shadowProj ;
};

}