//этот класс нужен для отрисовки примитивов типа куба, шара, цилиндра и так далее 
// этот класс временно нужен будет только для скайбокса 
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include "shader.h"

float skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
	
		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
	
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
	
		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
	
		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
	
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
};

class Shape{
public:

	unsigned int skyboxID = 0;
    void LoadSkyBox(std::vector<std::string> path) {
		skyboxShader = Shader("../../shaders/skybox.vert", "../../shaders/skybox.frag");
		
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

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

        skyboxShader.use();
    	skyboxShader.setInt("skybox", 0);
	}

    void DrawSkyBox(glm::mat4 view_camera, glm::mat4 projection){

        glDepthFunc(GL_LEQUAL); // меняем функцию глубины, чтобы обеспечить прохождение теста глубины, когда значения равны содержимому буфера глубины
        skyboxShader.use();
        glm::mat4 view = glm::mat4(glm::mat3(view_camera)); // убираем из матрицы вида секцию, отвечающую за операцию трансляции
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);


        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // восстанавливаем стандартное значение функции теста глубины
    }


private:

	void CreateSkyBox(){
		
	}


    unsigned int VAO, VBO;
    Shader skyboxShader;
	
    

};