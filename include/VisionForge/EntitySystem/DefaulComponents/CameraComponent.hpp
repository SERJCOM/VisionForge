#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
// #include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/EntitySystem/Component.hpp"
#include "VisionForge/EntitySystem/Components/CameraInterface.hpp"

namespace vision
{

	class CameraComponent : public ICameraComponents
	{
	public:
		void Start() override;

		void Update() override
		{
			Looking();
			updateView();
		}

		CameraComponent() {}

		void SetWindow(sf::Window &window)
		{
			window_ = &window;
		}

		CameraComponent(sf::Window &window) : window_(&window)
		{
			sf::Vector2i position;
			position.x = 400;
			position.y = 300;

			sf::Mouse::setPosition(position, *window_);
		}


		void Looking() override;

		glm::mat4 updateView()
		{
			view = glm::lookAt(pos_, pos_ + cameraFront, cameraUp);
			return view;
		}

		glm::mat4 GetViewMatrix() const override
		{
			return view;
		}

		void SetSensitivity(float sensitivity)
		{
			sensitivity_ = sensitivity;
		}

		float GetSensitivity() const
		{
			return sensitivity_;
		}


		glm::vec3 GetCameraUp() const override
		{
			return cameraUp;
		}

		glm::vec3 GetCameraFront() const override
		{
			return cameraFront;
		}

		virtual ~CameraComponent() = default;

	private:
		float yaw = 0, pitch = 0;
		float xpos = 400, ypos = 300;
		float lastX = xpos, lastY = ypos;
		float sensitivity_ = 0.1;
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 view;

	protected:
		sf::Window *window_;
	};

}