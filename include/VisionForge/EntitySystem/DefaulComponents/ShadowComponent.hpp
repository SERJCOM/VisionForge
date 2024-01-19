#pragma once 

#include "VisionForge/EntitySystem/Components/ShadowInterface.hpp"
#include "VisionForge/System/Shader.hpp"

#include <iostream>
#include "VisionForge/Common/Common.hpp"

namespace vision{

class PointShadow : public IShadow{
public:

    PointShadow(){
        // generator_index = 0;
        name_struct_ = "point_light_shadow";
        index = generator_index;
    }

    void Init();

    void Prepare() override{

        glViewport(0, 0, width, height);
        glClear(GL_DEPTH_BUFFER_BIT);

        shadow_shader.use();

        UpdateShadowTransform();

        for(int i = 0; i < shadowTransforms.size(); i++){
            shadow_shader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
        }

        shadow_shader.setFloat("far_plane", far);
        shadow_shader.setVec3("lightPos", pos_);

        // std::cout << "позиция источника тени в подготовке" << pos_ << std::endl;
        

    }

    void Update() override{}

    void Start() override;

    void UseShadow(Shader& shader) override {

        

    }

    Shader& GetShader() {
        return shadow_shader;
    }

private:



    void UpdateShadowTransform(); 

    static int generator_index;
    int index = 0;

    std::vector<glm::mat4> shadowTransforms;
    float aspect;
    glm::mat4 shadowProj ;
};

}