#pragma once

#include <functional>
#include <memory>
#include <SFML/Window.hpp>
#include <filesystem>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include "VisionForge/System/Framebuffer.hpp"

namespace vision
{

	class System
	{

	private:
		std::function<void(int &drawning)> gameLoop;

	public:
		System();

		void Init();

		void TurnOnCullFace();

		void Drawning(int x, int y);

		void SetGameLoop(std::function<void(int &drawning)> loop);

		sf::Window &GetWindow();

		std::filesystem::path GetCurrentPath() const;

		void SetMainCamera(vision::CameraComponent *main_camera);

		void SetEnginePtr(Engine *eng)
		{
			engine_ = eng;
		}

		void SetProjectionMatrix(glm::mat4 projection);

		glm::mat4 GetProjectionMatrix() const;

		vision::CameraComponent *GetMainCamera() const;

		Shader &GetMainShader();

		Shader * GetCurrentShader();

		void Display();

		void TestShadows(){ // просто тест теней
			
			glGenTextures(1, &depthCubemap);

			
			glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
			for (unsigned int i = 0; i < 6; ++i)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
							SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);  

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  

			
			glGenFramebuffers(1, &depthMapFBO);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);  

			float aspect = (float)SHADOW_WIDTH/(float)SHADOW_HEIGHT;
			float near = 1.0f;
			far = 25.0f;
			glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), aspect, near, far); 

			lightPos = glm::vec3(5, 1, 1);

			shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
shadowTransforms.push_back(shadowProj * 
                 glm::lookAt(lightPos, lightPos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
shadowTransforms.push_back(shadowProj * 
                 glm::lookAt(lightPos, lightPos + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
shadowTransforms.push_back(shadowProj * 
                 glm::lookAt(lightPos, lightPos + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)));
shadowTransforms.push_back(shadowProj * 
                 glm::lookAt(lightPos, lightPos + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)));
shadowTransforms.push_back(shadowProj * 
                 glm::lookAt(lightPos, lightPos + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0)));
		}

	private:
		///////////////////
		const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
		unsigned int depthCubemap;
		unsigned int depthMapFBO;

		Shader shadow;

		std::vector<glm::mat4> shadowTransforms;

		glm::vec3 lightPos;

		float far ;

		////////////////////////////

		void UpdateMatrix();

		void UpdateShader();

		sf::Window window_;

		Shader shad_;

		Shader* current_shader_ = nullptr;

		Engine *engine_ = nullptr;

		std::filesystem::path current_path_;

		glm::mat4 projection_;
		glm::mat4 view_;

		vision::CameraComponent *main_camera_;

		std::unique_ptr<FrameBuffer> main_buffer_;
	};

}