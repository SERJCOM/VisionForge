#pragma once
#include <iostream>
#include "window.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include <SFML/Graphics/Image.hpp>



class Engine
{
public:
	Engine(){
		glewInit();
		glEnable(GL_TEXTURE_CUBE_MAP);
		glEnable(GL_DEPTH_TEST);
		
	}

	void TurnOnCullFace(){
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK); 
	}

	void ClearBuffers(){
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Drawning(int x, int y){
		glViewport(0, 0, x, y);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_CULL_FACE);
	}
};
