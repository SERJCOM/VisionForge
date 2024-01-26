#pragma once
#include <iostream>
#include <GL/glew.h>
#include <memory>
#include <cassert>
#include <vector>

namespace vision
{

    class FrameBuffer
    {
    public:
        FrameBuffer(){
            glGenFramebuffers(1, &fbo);
        }

        FrameBuffer(int fbo){
            this->fbo = fbo;
        }



        FrameBuffer(FrameBuffer&) = delete;
        FrameBuffer& operator=(FrameBuffer&) = delete;



        virtual ~FrameBuffer(){
            if(fbo != 0)
                glDeleteFramebuffers(1, &fbo);
        }

        virtual void Init(){}

        virtual void UseBuffer(){
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        }

        virtual void DontUseBuffer(){
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        virtual void ClearBuffer(){
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        int GetFBO() const {
            return fbo;
        }

        virtual int GetTexture()
        {
            std::cerr << "This method is not supported" << std::endl;
            assert(false);
        }

        virtual std::vector<unsigned int> GetTextures(){
            std::cerr << "This method is not supported" << std::endl;
            assert(false);
        }

        protected:


        unsigned int fbo ;

    };


    std::unique_ptr<FrameBuffer> CreateCommonFrameBuffer(int fbo = -1);
    std::unique_ptr<FrameBuffer> CreateTextureWrittingFrameBuffer(int width, int height);
    

}