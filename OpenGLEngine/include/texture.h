#pragma once
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>

namespace Engine {
	class Texture {
	public:
		sf::Image skybox[6];
		
		unsigned int LoadSkyBox(){
			unsigned int skyboxID;
			glGenTextures(1, &skyboxID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

			skybox[0].loadFromFile("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/skybox1.jpg");
			skybox[1].loadFromFile("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/skybox2.jpg");
			skybox[2].loadFromFile("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/skybox3.jpg");
			skybox[3].loadFromFile("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/skybox4.jpg");
			skybox[4].loadFromFile("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/skybox5.jpg");
			skybox[5].loadFromFile("D:/prog/проекты VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/skybox6.jpg");

			for (int i = 0; i < 6; i++) {
				glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, skybox[i].getSize().x , skybox[i].getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, skybox[i].getPixelsPtr()
				);

				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			}

			
			glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
			return skyboxID;
		}
	};
}