#pragma once
#include <vector>
#include <SFML/Graphics/Image.hpp>
#include <string>
#include <filesystem>

#include "VisionForge/System/Shader.hpp"

namespace vision
{

	class Skybox
	{
	public:
		Skybox(Shader *main_shader);

		void LoadSkyBox(std::filesystem::path filepath);

		void DrawSkyBox(glm::mat4 view_camera, glm::mat4 projection);

	private:
		void LoadRGBEfile(std::string path);

		void CreateHDRTexture();

		void CreateEnvironment();

		void CreatePrefilterMap();

		unsigned int GetEnvironmentTexture();

		unsigned int GetPrefilterTexture();

		unsigned int GetBDRFTexture();

		void CreateBRDF();

		unsigned int skyboxID = 0, quadVAO = 0, quadVBO = 0;
		Shader BRDF;

		unsigned int VAO = 0, VBO = 0;
		unsigned int HDRTexture = 0, envirTexture = 0, prefilterMap = 0, brdfTexture = 0;

		unsigned int captureFBO, captureRBO;
		glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
		glm::mat4 captureViews[6] = {
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
			glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f))};

		Shader skyboxShader;
		Shader HDRShader;
		Shader prefilter;

		Shader *main_shader_ = nullptr;
	};

}