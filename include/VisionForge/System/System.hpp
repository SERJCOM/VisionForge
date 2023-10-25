#pragma once
#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <vector>
#include <memory>
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/EntitySystem/Entity.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <utility>
#include <filesystem>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VisionForge/System/Shader.hpp"
#include "VisionForge/EntitySystem/DefaulComponents/CameraComponent.hpp"
#include <cassert>

//#include "VisionForge/EntitySystem/EntitySystem.hpp"
#include "VisionForge/System/Framebuffer.hpp"

namespace vision
{
	class Engine;

	class System
	{

	private:
		std::function<void(int &drawning)> gameLoop;

	public:
		System();

		void Init();

		void TurnOnCullFace();

		void ClearBuffers();

		void Drawning(int x, int y);

		void SetGameLoop(std::function<void(int &drawning)> loop);

		sf::Window &GetWindow();

		std::filesystem::path GetCurrentPath() const;

		void SetMainCamera(vision::CameraComponent *main_camera);

		void SetEnginePtr(Engine* eng){
			engine_ = eng;
		}

		void SetProjectionMatrix(glm::mat4 projection);

		glm::mat4 GetProjectionMatrix() const;

		vision::CameraComponent *GetMainCamera() const;

		Shader &GetMainShader();

		const Shader &GetMainShader() const;

		void Display();

	private:
		void UpdateMatrix();

		void UpdateShader();

		// std::vector<std::shared_ptr<vision::IEntity>> entities_;
		// std::vector<std::unique_ptr<vision::IComponent>> components_;
		sf::Window window_;

		Shader shad_;
		Shader shadow_;

		Engine* engine_ = nullptr;

		std::filesystem::path current_path_;

		glm::mat4 projection_;
		glm::mat4 view_;

		vision::CameraComponent *main_camera_;

		std::unique_ptr<IFrameBuffer> main_buffer_;
	};

    // template <typename T>
    // inline T *System::RegisterComponent()
    // {
    //     components_.push_back(std::make_unique<T>());
	// 	return components_.back().get();
    // }

}