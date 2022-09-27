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

    glm::mat4 lightView ;
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane); 

public:

    Shadow(int width, int height){
        lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), 
                                  glm::vec3( 0.0f, 0.0f,  0.0f), 
                                  glm::vec3( 0.0f, 1.0f,  0.0f));  

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
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void SetMat4(){
        shad.use();
        shad.setMat4("shadowmatrix", lightProjection * lightView);  
    }

    Shader GetShader(){
        return shad;
    }

    GLuint GetTexture(){
        return texture;
    }

};