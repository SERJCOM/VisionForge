#pragma once
#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <vector>
#include <memory>
#include "Component.hpp"
#include "Entity.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <utility>
#include <filesystem>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "CameraComponent.h"
#include <cassert>

namespace lthm{

class Engine
{
private:
	std::function<void(int& drawning)> gameLoop;

public:
	Engine() {

		using namespace std::filesystem;

		window_.create(sf::VideoMode({800, 600}), "OpenGL");
		window_.setActive();

		Init();

		current_path_ = std::filesystem::current_path() / path("../shaders");
		current_path_ = current_path_.lexically_normal();

		shad_ = Shader(current_path_ / path("shader.vert"), current_path_  /  path("shader.frag"));
		shadow_ = Shader(current_path_ / path("shadow.vert"), current_path_ / path("shadow.frag"));

		projection_ = glm::perspective(glm::radians(80.0f), (float)GetWindow().getSize().x / (float)GetWindow().getSize().y, 0.1f, 1000.0f);
	}

	void Init(){
		glewInit();

		glEnable(GL_TEXTURE_CUBE_MAP);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void TurnOnCullFace() {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); 
	}

	void ClearBuffers() {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Drawning(int x, int y) {
		glViewport(0, 0, x, y);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_CULL_FACE);
	}

	void SetGameLoop(std::function<void(int& drawning)> loop){
		gameLoop = loop;
	}


	sf::Window& GetWindow() {
		return window_;
	}

	void AddEntity(std::shared_ptr<lthm::IEntity> entity){
		entity->Start();
		entities_.push_back(entity);

		auto components = entity->GetComponents();
		for(auto component : components){
			RegisterComponent(component);
		}
	}

	void RegisterComponent(std::shared_ptr<lthm::IComponent> component){
		components_.push_back(component);
	}

	std::filesystem::path GetCurrentPath() const {
		return current_path_;
	}

	void SetMainCamera(lthm::CameraComponent* main_camera){
		main_camera_ = main_camera;
	}

	void SetProjectionMatrix(glm::mat4 projection){
		projection_ = projection;
	}

	glm::mat4 GetProjectionMatrix() const {
		return projection_;
	}

	lthm::CameraComponent* GetMainCamera() const {
		return main_camera_;
	}

	Shader& GetMainShader()  {
		return shad_;
	}

	const Shader& GetMainShader() const {
		return shad_;
	}


	void Display() {
		int drawning = 1;
		while(true){

			if(drawning == 0){
				break;
			}

			try{

				Drawning(GetWindow().getSize().x ,GetWindow().getSize().y);
				ClearBuffers();
				
				for(auto entity : entities_){
					entity->Update();
				}

				for(auto component : components_){
					component->Update();
				}

				UpdateMatrix();
				UpdateShader();
				
				gameLoop(drawning);
				window_.display();

			}
			catch (...){
				std::cout << "ERROR::UNKNOW ERROR!!!" << std::endl;
			}

		}
	}

private:

	void UpdateMatrix(){

		view_ = main_camera_->GetViewMatrix();
		
	}

	void UpdateShader(){
		shad_.use();
		shad_.setMat4("projection", projection_);
		shad_.setMat4("view", view_);
		shad_.setVec3("cameraPos", main_camera_->GetCameraPos());
	}


	std::vector<std::shared_ptr<lthm::IEntity>> entities_;
	std::vector<std::shared_ptr<lthm::IComponent>> components_;
	sf::Window window_;

	Shader shad_;
	Shader shadow_;

	std::filesystem::path current_path_;

	glm::mat4 projection_;
	glm::mat4 view_;

	lthm::CameraComponent* main_camera_;
};


}