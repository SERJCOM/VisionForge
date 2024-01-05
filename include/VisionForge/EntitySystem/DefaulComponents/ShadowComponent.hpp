#pragma once 

#include "VisionForge/EntitySystem/Components/ShadowInterface.hpp"
#include "VisionForge/System/Shader.hpp"



namespace vision{

class PointShadow : public IShadow{
public:

    PointShadow(){

    }

    void Init();

    void Prepare() override{
        glViewport(0, 0, width, height);
        glClear(GL_DEPTH_BUFFER_BIT);

        shadow_shader.use();

        for(int i = 0; i < shadowTransforms.size(); i++){
            shadow_shader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
        }

        shadow_shader.setFloat("far_plane", far);
        shadow_shader.setVec3("lightPos", pos_);

    }

    void Update() override{

    }

    void Start() override;

    Shader& GetShader() {
        return shadow_shader;
    }

private:

    void UpdateShadowTransform(); 

    Shader shadow_shader;
    std::vector<glm::mat4> shadowTransforms;
    float aspect;
    glm::mat4 shadowProj ;
};

}