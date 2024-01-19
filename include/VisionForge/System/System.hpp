#pragma once

#include <functional>
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <filesystem>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VisionForge/System/Shader.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include "VisionForge/System/Framebuffer.hpp"

#include "VisionForge/EntitySystem/DefaulComponents/ShadowComponent.hpp"

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
		sf::RenderWindow& GetRenderWindow(){
			return window_;
		}

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

		virtual void Display();

		virtual void Start();

	private:

		void Render();

		void UpdateMatrix();

		void UpdateShader();

		sf::RenderWindow window_;

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