#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
//#include "VisionForge/Engine/Engine.hpp"
#include "VisionForge/EntitySystem/Component.hpp"


namespace vision{

class CameraComponent : public vision::IComponent{
public:

	void Start() override;

	void Update() override{
		Looking();
		updateView();
	}
	
	CameraComponent() {}

	void SetWindow(sf::Window& window){
		window_ = &window;
	}

	CameraComponent(sf::Window& window):window_(&window) {
		sf::Vector2i position;
		position.x = 400;
		position.y = 300;

		sf::Mouse::setPosition(position, *window_);

	}

	void SetCameraPosition(glm::vec3 pos){
		cameraPos = pos;
	}

	virtual void Looking() ;

	glm::mat4 updateView() {
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		return view;
	}

	virtual glm::mat4 GetViewMatrix() const {
		return view;
	}

	void SetSensitivity(float sensitivity){
		sensitivity_ = sensitivity;
	}

	float GetSensitivity() const {
		return sensitivity_;
	}

	glm::vec3 GetCameraPos() const {
		return cameraPos;
	}

	glm::vec3 GetCameraUp() const {
		return cameraUp;
	}

	glm::vec3 GetCameraFront() const {
		return cameraFront;
	}


	virtual ~CameraComponent() = default;

private:
	float yaw = 0, pitch = 0;	
	float xpos = 400, ypos = 300;	
	float lastX = xpos, lastY = ypos;
	float sensitivity_ = 0.1;
	glm::vec3 cameraPos = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;

protected:
	sf::Window* window_;
};

}