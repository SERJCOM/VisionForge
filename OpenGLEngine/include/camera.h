#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

class Camera {
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float cameraspeed = 0.1;


	glm::vec3 SetMatrix(float x, float y, float z) {
		return glm::vec3(x,	y, z);
	}

	void CameraMove() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { 
			cameraPos+= cameraspeed *cameraFront; 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPos -= cameraspeed * cameraFront;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraspeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraspeed;
		//std::cout << cameraPos.x << " " <<  cameraPos.y << " " << cameraPos.z << std::endl;
	}
};