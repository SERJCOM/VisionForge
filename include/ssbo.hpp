#pragma once
#include <iostream>
#include <GL/glew.h>
#include <vector>

class SSBO{
public:

    GLuint GetSSBO(){
        return ssbo;
    }

    void Init(void *data, int size, int index){
        const void* _data = data;
        glGenBuffers(1, &ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBufferData(GL_SHADER_STORAGE_BUFFER, size, _data, GL_STATIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind
    }

    void Bind(){
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }


private:
    GLuint ssbo;
};