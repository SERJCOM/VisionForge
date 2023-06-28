#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>



class CameraEntity {
public:
	glm::vec3 cameraPos = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
	

	CameraEntity(sf::Window& window):window_(window) {
		sf::Vector2i position;
		position.x = 400;
		position.y = 300;

		sf::Mouse::setPosition(position, window_);
	
	}


	virtual void Move() {
		const float cameraSpeed = 0.5f;
		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))	cameraPos += cameraSpeed * cameraFront;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))	cameraPos -= cameraSpeed * cameraFront;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


	}

	virtual void Looking() {
		
		float xoffset = -(lastX - xpos);
		float yoffset = -(ypos - lastY);

		const float sensitivity = 0.01f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;


		yaw += xoffset;	
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;


		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);


		sf::Vector2i pos = sf::Mouse::getPosition(window_);
		xpos = pos.x;
		ypos = pos.y;

		sf::Vector2i position;
		position.x = 400;
		position.y = 300;
		sf::Mouse::setPosition(position, window_); 
	}

	glm::mat4 updateView() {
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		return view;
	}

	virtual ~CameraEntity() = default;

protected:
	float lastX = 400, lastY = 300;
	float yaw = 0, pitch = 0;	
	float xpos = 400, ypos = 300;	
	sf::Window& window_;
};