#include "VisionForge/System/Framebuffer.hpp"

#include <unordered_map>

using namespace vision;

class CommonFrameBuffer : public FrameBuffer
{
public:
    CommonFrameBuffer() : FrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        textures.resize(6);

        for (int i = 0; i < 3; i++)
        {

            glGenTextures(1, &textures[i]);
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1080, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures[i], 0);
        }

        name_texture_ = {{"screenTexture", 0}, {"godRaysSampler", 1}, {"bloomBlur", 2}, 
            {"gPosition", 3}, {"gNormal", 4},  {"gAlbedoSpec", 5}
        };

        glGenTextures(1, &textures[name_texture_.at("gPosition")]);
        glBindTexture(GL_TEXTURE_2D, textures[name_texture_.at("gPosition")]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1080, 720, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, textures[name_texture_.at("gPosition")], 0);
        
        // Цветовой буфер нормалей
        glGenTextures(1, &textures[name_texture_.at("gNormal")]);
        glBindTexture(GL_TEXTURE_2D, textures[name_texture_.at("gNormal")]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, 1080, 720, 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, textures[name_texture_.at("gNormal")], 0);
        
        // Цветовой буфер цвета + отраженной составляющей
        glGenTextures(1, &GetTextureByName("gAlbedoSpec"));
        glBindTexture(GL_TEXTURE_2D, GetTextureByName("gAlbedoSpec"));
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1080, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, GetTextureByName("gAlbedoSpec"), 0);
        

        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1080, 720);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
    }

    void UseBuffer() override{
        FrameBuffer::UseBuffer();
        unsigned int attachments[6] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, 
        GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5};
        glDrawBuffers(6, attachments);
    }



    unsigned int &GetTexture() override
    {
        return textures[0];
    }

    std::vector<unsigned int> GetTextures() override
    {
        return textures;
    }

    virtual unsigned int &GetTextureByName(std::string_view name) override{
        return textures[name_texture_.at(name.data())];
    }




private:

    std::vector<unsigned int> textures;

    std::unordered_map<std::string, unsigned int> name_texture_;

    unsigned int rbo;


    // std::vector<unsigned int> attachments;
};

std::unique_ptr<FrameBuffer> vision::CreateCommonFrameBuffer(int fbo)
{
    return std::make_unique<CommonFrameBuffer>();
}

class TextureWRFramebuffer : public FrameBuffer
{

private:
    unsigned int texture, rbo, framebuff, width, height;

public:
    TextureWRFramebuffer(int width, int height)
    {

        this->width = width;
        this->height = height;

        glGenFramebuffers(1, &framebuff);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "ERROR. Framebuffer was NOT done" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void ClearBuffer() override
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void UseBuffer() override
    {
        glViewport(0, 0, width, height);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuff);
        ClearBuffer();
    }

    unsigned int &GetTexture()
    {
        return texture;
    }
};

std::unique_ptr<FrameBuffer> vision::CreateTextureWrittingFrameBuffer(int width, int height)
{
    return std::make_unique<TextureWRFramebuffer>(width, height);
}
