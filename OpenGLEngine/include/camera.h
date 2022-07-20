#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

using	std::cout;
using	std::endl;

class Camera {
public:
	glm::vec3 cameraPos = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;

	

	Camera(sf::Window* window) {
		sf::Vector2i Position;
		Position.x = 400;
		Position.y = 300;
		sf::Mouse::setPosition(Position, *window);
	}

	void move() {
		const float cameraSpeed = 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraPos += cameraSpeed * cameraFront;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPos -= cameraSpeed * cameraFront;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	void looking(sf::Window* window) {

		window->setMouseCursorVisible(false);
		
		
		float xoffset = -(lastX - xpos);
		float yoffset = -(ypos - lastY);

		const float sensitivity = 0.05f;
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

		sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
		xpos = localPosition.x;
		ypos = localPosition.y;
		//cout << xpos << " " << ypos << endl;

		sf::Vector2i Position;
		Position.x = 400;
		Position.y = 300;
		sf::Mouse::setPosition(Position, *window);
	}

	glm::mat4 updateView() {
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

private:
	float lastX = 400, lastY = 300;
	float yaw = 0, pitch = 0;
	float xpos = 400, ypos = 300;
};