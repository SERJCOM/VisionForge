#pragma once
#include <iostream>
#include <functional>
#include <GL/glew.h>
#include <vector>
#include <memory>
#include "collection.hpp"
#include "Entity.hpp"
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <utility>

namespace lthm{

class Engine
{
private:
	std::function<void(int& drawning)> gameLoop;

public:
	Engine() {
		window_.create(sf::VideoMode({800, 600}), "OpenGL");
		window_.setActive(true);

		Init();
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


	void Display() {
		int drawning = 1;
		while(true){
			gameLoop(drawning);
			try{
				for(const auto& entity : entities_){
					entity->Update();
				}

				for(const auto& component : components_){
					component.get()->Update();
				}

				if(drawning == 0){
					break;
				}

			}
			catch (...){
				std::cout << "ERROR::UNKNOW ERROR!!!" << std::endl;
			}

			window_.display();
		}

		
	}

private:
	std::vector<std::shared_ptr<Collection>> components_;
	std::vector<std::shared_ptr<lthm::Entity>> entities_;
	sf::Window window_;
};


}