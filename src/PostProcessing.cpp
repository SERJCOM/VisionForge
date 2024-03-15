#include "VisionForge/Engine/PostProcessing.hpp"
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "VisionForge/Common/Common.hpp"


void vision::PostProcessingManager::Start()
{
    float quadVertices[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f};


    post_processing_ = Shader(GetShaderPath("postproc.vert"), GetShaderPath("postproc.frag") );

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));


    sun_ = std::make_unique<post::Sun>();
    sun_->Start();

    screen_resolution_.height = 720;
    screen_resolution_.width = 1080;
}

void vision::PostProcessingManager::Update(Shader& default_shader)
{
    default_shader.setInt("mode_render", 2);
    sun_->Draw(default_shader);
    default_shader.setInt("mode_render", 1);
}


void vision::PostProcessingManager::UsePostProcessing(FrameBuffer* buffer, glm::mat4 projection, glm::mat4 view)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screen_resolution_.width, screen_resolution_.height);
    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    post_processing_.use();
    glBindVertexArray(quadVAO);

    glm::vec4 sunpos = projection * view * glm::vec4(sun_->GetObjectPosition(), 1.0);
    glm::vec3 normsunpos = glm::vec3(sunpos.x / sunpos.w, sunpos.y / sunpos.w, sunpos.z / sunpos.w);

    post_processing_.setInt("bloomBlur", 1);
    post_processing_.SetTexture(1, buffer->GetTextures()[2], "bloomBlur");

    post_processing_.setInt("screenTexture", 15);
    post_processing_.SetTexture(15, buffer->GetTexture(), "screenTexture");

    post_processing_.setInt("godRaysSampler", 16);
    post_processing_.SetTexture(16, buffer->GetTextures()[1], "godRaysSampler");
    post_processing_.setVec3("sunPos", normsunpos);

    post_processing_.setInt("gPosition", 2);
    post_processing_.SetTexture(2, buffer->GetTextureByName("gPosition"), "gPosition");

    post_processing_.setInt("gNormal", 3);
    post_processing_.SetTexture(3, buffer->GetTextureByName("gNormal"), "gNormal");


    post_processing_.setInt("gAlbedoSpec", 4);
    post_processing_.SetTexture(4, buffer->GetTextureByName("gAlbedoSpec"), "gAlbedoSpec");


    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
}