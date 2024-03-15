#include "VisionForge/Engine/PostProc/Blur.hpp"
#include "VisionForge/Common/Common.hpp"

using namespace vision;

using namespace post;


void Blur::BlurTexture(int texture){
    bool horizontal = true, first_iteration = true;
    int amount = 10;
    shader.use();
    shader.setInt("image", 2);
    // shader.SetTexture(2, texture, "image");
    
    for (unsigned int i = 0; i < amount; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]); 
        shader.setInt("horizontal", horizontal);
        shader.SetTexture(2, first_iteration ? texture : pingpongBuffer[!horizontal], "image");
        // glBindTexture(
        //     GL_TEXTURE_2D, 
        // ); 
        RenderQuad();
        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}