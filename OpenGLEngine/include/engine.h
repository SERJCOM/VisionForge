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
	class Engine : public Camera
	{
	public:
		Shader shader;
		Object object1;
		Texture texture1;

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

			float vertices[] = {
				0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   
				0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   
			   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
			   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    
			};

			unsigned int indices[] = {  
				0, 1, 3,  
				1, 2, 3   
			};

			object1.LoadArray(vertices, sizeof(vertices) / sizeof(float));
			object1.LoadArrayEBO(indices, sizeof(indices) / sizeof(int));

			object1.Create();
			texture1.LoadTexture();

		}

		void ClearBuffers() {
			glClearColor(0.2, 0.8, 1, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Push() {
			object1.SetMatrixShader(object1.modelVatrix(-55.0f), object1.viewMatrix(0, 0, -3), object1.projectionMatrix(), shader.ID);
			shader.use();
			glBindTexture(GL_TEXTURE_2D, texture1.texture);
			glBindVertexArray(object1.VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glFlush();
		}

		
	};
};