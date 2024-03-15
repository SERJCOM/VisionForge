#pragma once

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/Common/Common.hpp"

namespace vision
{

    namespace post
    {

        class Blur
        {
        public:
            Blur()
            {
            }

            void ConfigureBlur(int width, int height)
            {
                shader = Shader(GetShaderPath("postproc.vert"), GetShaderPath("blur.frag"));
                glGenFramebuffers(2, pingpongFBO);
                glGenTextures(2, pingpongBuffer);

                for (unsigned int i = 0; i < 2; i++)
                {
                    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
                    glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
                    glTexImage2D(
                        GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glFramebufferTexture2D(
                        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0);
                }
            }

            void BlurTexture(int texture);

        private:
            Shader shader;

            unsigned int pingpongFBO[2];
            unsigned int pingpongBuffer[2];
        };

    }

}