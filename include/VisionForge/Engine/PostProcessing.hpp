#pragma once
#include "VisionForge/Engine/PostProc/Blur.hpp"
#include "VisionForge/Engine/PostProc/Sun.hpp"
#include "VisionForge/System/Shader.hpp"
#include "VisionForge/System/Framebuffer.hpp"

namespace vision{


class PostProcessingManager{
public:
    PostProcessingManager() = default;

    PostProcessingManager(int width, int height){
        screen_resolution_.width = width;
        screen_resolution_.height = height;
    }



    void Start();

    void Update(Shader& default_shader);

    void UsePostProcessing(FrameBuffer* buffer, glm::mat4 projection, glm::mat4 view);

    void SetBlurMode(bool mode);

    void SetSunMode(bool mode);

    void SetScreenResolution(int width, int height);


    struct ScreenResolution{
        int width;
        int height;
    };

    ScreenResolution GetScreenResolution() const {
        return screen_resolution_;
    }

private:
    

    ScreenResolution screen_resolution_;

    Shader post_processing_;

    unsigned int quadVAO, quadVBO;

    std::unique_ptr<post::Sun> sun_;

};

}