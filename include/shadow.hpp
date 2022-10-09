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
    glm::vec3 position = glm::vec3(10.0f, 40.0f, 30.0f);
    glm::vec3 *ptrPosition = &position;
    glm::vec3 look = glm::vec3(0,0,0);

    glm::mat4 lightView = glm::lookAt(*ptrPosition, look , glm::vec3(0.0, 1.0, 0.0));
    float near_plane = 1.0f, far_plane = 1000.5f;
    glm::mat4 lightProjection = glm::ortho(-500.0f, 500.0f, -500.0f, 500.0f, near_plane, far_plane); 

    bool type = false; // false = orth; 

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
        // glEnable(GL_CULL_FACE);
		// glCullFace(GL_FRONT); 
    }

    void SetMat4(){
        glm::mat4 lightView;
        if(!type)
            lightView = glm::lookAt(*ptrPosition, look , glm::vec3(0.0, 1.0, 0.0));
        shad.use();
        shad.setMat4("lightSpaceMatrix", lightProjection * lightView);  
    }

    void SetMat4(glm::mat4 look){
        shad.use();
        shad.setMat4("lightSpaceMatrix", look);
    }

    void SetPosition(glm::vec3 position){
        this->position = position;
    }

    void SetPosition(glm::vec3* pos){
        ptrPosition = pos;
    }

    glm::mat4 GetMatrix(){
        return lightProjection * lightView;
    }

    Shader GetShader(){
        return shad;
    }

    GLuint GetTexture(){
        return texture;
    }

};