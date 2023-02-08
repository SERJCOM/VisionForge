#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "GLFW/glfw3.h"

using	std::cout;
using	std::endl;

class Camera {
public:
	glm::vec3 cameraPos = glm::vec3(-1.0f, 0.0f, 0.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
	

	Camera(GLFWwindow* window) {
		sf::Vector2i Position;
		Position.x = 400;
		Position.y = 300;
		//sf::Mouse::setPosition(Position, *window);
		glfwSetCursorPos(window, Position.x, Position.y);
		this->window = window;
	}


	void move() {
		const float cameraSpeed = 0.5f;
		// glfwSetKeyCallback(window, [&](GLFWwindow* window, int key, int scancode, int action, int mods){
		// 	if (key == GLFW_KEY_W && action == GLFW_PRESS)	cameraPos += cameraSpeed * cameraFront;
		// 	if (key == GLFW_KEY_S && action == GLFW_PRESS)	cameraPos -= cameraSpeed * cameraFront;
		// 	if (key == GLFW_KEY_A && action == GLFW_PRESS)	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		// 	if (key == GLFW_KEY_D && action == GLFW_PRESS)	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		// });

		int stateW = glfwGetKey(window, GLFW_KEY_W);
		int stateS = glfwGetKey(window, GLFW_KEY_S);
		int stateA = glfwGetKey(window, GLFW_KEY_A);
		int stateD = glfwGetKey(window, GLFW_KEY_D);

		if(stateW == GLFW_PRESS)	cameraPos += cameraSpeed * cameraFront;
		if(stateS == GLFW_PRESS)	cameraPos -= cameraSpeed * cameraFront;
		if(stateA == GLFW_PRESS)	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if(stateD == GLFW_PRESS)	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraPos += cameraSpeed * cameraFront;
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPos -= cameraSpeed * cameraFront;
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		// if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	void looking(GLFWwindow* window) {

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		
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

		double _xpos, _ypos;
		glfwGetCursorPos(window, &_xpos, &_ypos);
		xpos = static_cast<float>(_xpos);
		ypos = static_cast<float>(_ypos);
		//std::cout << "xpos ypos " << xpos << " " << ypos << std::endl;

		sf::Vector2i Position;
		Position.x = 400;
		Position.y = 300;
		glfwSetCursorPos(window, Position.x, Position.y);
		//sf::Mouse::setPosition(Position, *window);
	}

	glm::mat4 updateView() {
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	

private:
	float lastX = 400, lastY = 300;
	float yaw = 0, pitch = 0;	
	float xpos = 400, ypos = 300;	
	GLFWwindow* window;
};