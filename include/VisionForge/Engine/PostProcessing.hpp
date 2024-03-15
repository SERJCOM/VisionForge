#pragma once
#include "VisionForge/Engine/PostProc/Blur.hpp"
#include "VisionForge/Engine/PostProc/Sun.hpp"
#include "VisionForge/System/Shader.hpp"
#include "VisionForge/System/Framebuffer.hpp"

namespace vision{


class PostProcessingManager{
public:
    PostProcessingManager() = default;

    void Start();

    void Update(Shader& default_shader);

    void UsePostProcessing(FrameBuffer* buffer, glm::mat4 projection, glm::mat4 view);

    void SetBlurMode(bool mode);

    void SetSunMode(bool mode);

    void SetScreenResolution(int width, int heig);


private:
    struct ScreenResolution{
        int width;
        int height;
    };

    ScreenResolution screen_resolution_;

    Shader post_processing_;

    unsigned int quadVAO, quadVBO;

    std::unique_ptr<post::Sun> sun_;

};

}