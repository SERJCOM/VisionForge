#pragma once
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>
#include <string>

class Texture {
public:
	unsigned int texture;
	unsigned int skyboxID = 0;

	void LoadSkyBox() {

		std::string path[6];
		path[0] = "D:/prog/������� VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/posx.jpg";
		path[1] = "D:/prog/������� VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/negx.jpg";
		path[2] = "D:/prog/������� VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/posy.jpg";
		path[3] = "D:/prog/������� VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/negy.jpg";
		path[4] = "D:/prog/������� VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/posz.jpg";
		path[5] = "D:/prog/������� VISUAL STUDIO/OpenGLEngine/OpenGLEngine/textures/negz.jpg";

		
		glGenTextures(1, &skyboxID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);

		for (int i = 0; i < 6; i++) {
			sf::Image image;
			if (!image.loadFromFile(path[i].c_str())) {
				std::cout << "failed to load the texture" << std::endl;
			}
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()
			);

			
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}


	static unsigned int LoadTextureFromFile(std::string name, std::string path) {
		unsigned int texture;
		sf::Image texture_im;
		if (texture_im.loadFromFile((path + "/" + name).c_str())) {

			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_im.getSize().x, texture_im.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_im.getPixelsPtr());
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			return texture;
		}
		else {
			std::cout << "failed to load the texture" << std::endl;
			return -1;
		}
	}

};


