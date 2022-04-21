#pragma once
#include <iostream>
#include "window.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "object.h"
#include "texture.h"
#include "shader.h"
#include <SFML/Graphics/Image.hpp>


namespace Engine {
	class Engine : public Camera, public Shader
	{
	public:

		Engine(){
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_CUBE_MAP);
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glClearDepth(1.f);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

		}

		void ClearBuffers() {
			glClearColor(0.2, 0.8, 1, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void DrawObject(unsigned int VAO, unsigned int texture) {
			
			use();
			glBindTexture(GL_TEXTURE_2D, texture);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glFlush();
		}
		
	};
};