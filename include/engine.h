#pragma once
#include <iostream>
#include <GL/glew.h>
#include <functional>
#include "GLFW/glfw3.h"
#include <vector>
#include <memory>
#include "collection.hpp"
#include "entity.hpp"


class Engine
{
private:
	std::function<void(int& drawning)> gameLoop;

public:
	Engine() {
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

	// void Display() const{
	// 	int drawning = 1;
	// 	while(true){
	// 		gameLoop(drawning);
	// 		if(!drawning)
	// 			break;
	// 	}

	// 	glfwTerminate();
	// }

	void Display() const{
		int drawning = 1;
		while(true){
			try{
				for(const auto& entity : _entities){
					entity.get()->Update();
				}

				for(const auto& component : _components){
					component.get()->Update();
				}

				if(drawning == 0){
					break;
				}
			}
			catch (...){
				std::cout << "ERROR::UNKNOW ERROR!!!" << std::endl;
			}
		}
	}

private:
	std::vector<std::shared_ptr<Collection>> _components;
	std::vector<std::shared_ptr<Entity>> _entities;
};
