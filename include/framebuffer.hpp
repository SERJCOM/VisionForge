#pragma once 
#include <iostream>
#include <GL/glew.h>

class Framebuffer{

private:
    unsigned int fbo, texture, rbo, framebuff, width, height;

public:
    Framebuffer(int width, int height){

        this->width = width;
        this->height = height;

        glGenFramebuffers(1, &framebuff);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);   

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);  

        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);  
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
            std::cout << "ERROR. Framebuffer was NOT done" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ClearBuffers(){
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }


    void UseFrameBuffer(){
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
        ClearBuffers();
    }

    int GetTexture(){
        return texture;
    }

};