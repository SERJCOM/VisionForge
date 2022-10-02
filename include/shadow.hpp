#pragma once
#include <iostream>
#include <GL/glew.h>
#include "shader.h"
#include <string>

class Shadow{
private:
    Shader shad;
    int width, height;
    GLuint texture, framebuff;

    glm::mat4 lightView = glm::lookAt(glm::vec3(0, 300, 0), glm::vec3(0, 0, 0) , glm::vec3(0.0, 1.0, 0.0));
    float near_plane = 1.0f, far_plane = 500.5f;
    glm::mat4 lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane); 
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

public:

    Shadow(int width, int height){
        shad = Shader("..\\..\\shaders\\shadow.vert", "..\\..\\shaders\\shadow.frag");
        this->width = width;
        this->height = height;
        glGenFramebuffers(1, &framebuff); 
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  

        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  
    }

    void Listening(){
        SetMat4();
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
        glClear(GL_DEPTH_BUFFER_BIT);


    }

    void SetMat4(){
        shad.use();
        shad.setMat4("lightSpaceMatrix", lightSpaceMatrix);  
    }

    void SetMat4(glm::mat4 look){
        shad.use();
        shad.setMat4("lightSpaceMatrix", look);
    }

    glm::mat4 GetMatrix(){
        return lightSpaceMatrix;
    }

    Shader GetShader(){
        return shad;
    }

    GLuint GetTexture(){
        return texture;
    }

};