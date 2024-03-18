#pragma once

#include <functional>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <filesystem>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include "VisionForge/System/Framebuffer.hpp"

#include "VisionForge/EntitySystem/DefaulComponents/ShadowComponent.hpp"

#include "VisionForge/EntitySystem/VisualComponent.hpp"

#include "VisionForge/Engine/PostProc/Blur.hpp"

namespace vision
{

	class System
	{

	private:
		std::function<void(int &drawning)> gameLoop;

		System();

		static System* system_ptr_;

	public:
		
		static System* GetInstance();

		void Init(); //

		void TurnOnCullFace();

		void Drawning(int x, int y); //

		void SetGameLoop(std::function<void(int &drawning)> loop);

		sf::Window &GetWindow();
		sf::RenderWindow &GetRenderWindow()
		{
			// return window_;
		}

		GLFWwindow * GetGLFWWindow(){
			return window_;
		}


		std::filesystem::path GetCurrentPath() const;

		void SetMainCamera(vision::CameraComponent *main_camera);

		void SetProjectionMatrix(glm::mat4 projection);

		glm::mat4 GetProjectionMatrix() const;

		vision::CameraComponent *GetMainCamera() const;

		Shader &GetMainShader();

		Shader *GetCurrentShader();

		virtual void Display();

		virtual void Start();

		std::pair<int, int> GetWindowSize() const {
			int width, height;
			glfwGetWindowSize(window_, &width, &height);
			return {width, height};
		}

	private:
		void Render();

		void UpdateMatrix();

		void UpdateShader();

		void UsePostProcessing(int texture);

		void InitPostProcessing();

		// sf::RenderWindow window_;
		GLFWwindow* window_;

		Shader shad_;

		Shader *current_shader_ = nullptr;


		std::filesystem::path current_path_;

		glm::mat4 projection_;
		glm::mat4 view_;

		vision::CameraComponent *main_camera_;

		std::unique_ptr<FrameBuffer> main_buffer_;

		// post processing
		unsigned int quadVAO, quadVBO;

		Shader post_processing_;

		post::Blur blur;

		std::unique_ptr<IVisualComponent> visc;
	};

}