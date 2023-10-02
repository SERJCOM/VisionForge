//этот класс нужен для отрисовки примитивов типа куба, шара, цилиндра и так далее 
// этот класс временно нужен будет только для скайбокса 
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include "VisionForge/System/Shader.hpp"
#include <string>

#include <filesystem>



class Shape{
public:
	unsigned int skyboxID = 0, quadVAO = 0, quadVBO = 0;
	Shader 		BRDF;
    void LoadSkyBox(std::vector<std::string> path);

	void LoadRGBEfile(std::string path);

    void DrawSkyBox(glm::mat4 view_camera, glm::mat4 projection);

	void CreateHDRTexture();

	void CreateEnvironment();
 
	void CreatePrefilterMap();


	unsigned int GetEnvironmentTexture(){
		//std::cout << envirTexture << " envirTexture" << std::endl;
		return envirTexture;
	}

	unsigned int GetPrefilterTexture(){
		//std::cout << prefilterMap << " prefilterMap" << std::endl;
		return prefilterMap;
	}

	unsigned int GetBDRFTexture(){
		//std::cout << brdfTexture << " brdfTexture" << std::endl;
		return brdfTexture;
	}

	void CreateBRDF();

// private:
    unsigned int 	VAO = 0, VBO = 0;
	unsigned int 	 HDRTexture = 0, envirTexture = 0, prefilterMap = 0, brdfTexture = 0;

	unsigned int 	captureFBO, captureRBO;
	glm::mat4 		captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	glm::mat4 		captureViews[6] = {
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
	};	

    Shader 		skyboxShader;
	Shader 		HDRShader;
	Shader 		prefilter;
	
};