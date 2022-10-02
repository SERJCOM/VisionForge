#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

class Lighting{
public:

    Lighting(float ambient, float specular, glm::vec3 color): ambient(ambient), specular(specular), color(color){}

    void SetAmbient(float ambient){
        this->ambient = ambient;
    }
    void SetSpecular(float specular){
        this->specular = specular;
    }
    void SetColor(glm::vec3 color){
        this->color = color;
    }

    void SetShaderParameters(Shader* shader){
        shader->use();
    }

private:
    float ambient;
    float specular;
    glm::vec3 color;

};
