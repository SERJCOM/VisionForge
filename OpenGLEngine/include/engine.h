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


namespace Engine {
	class Engine : public Camera
	{
	public:
		struct map_color {
			float x, y, z;
		};

		Shader shader;
		Object object1;
		Texture texture1;

		Engine() {
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE_CUBE_MAP);
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glClearDepth(1.f);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum(-1, 1, -1, 1, 1, 5000);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			texture1.LoadTexture();

			float vertices1[] = {
				// координаты        // цвета            // текстурные координаты
				0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
				0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
			   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
			   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // верхняя левая 
			};

			unsigned int indices[] = {  // помните, что мы начинаем с 0!
					0, 1, 3, // первый треугольник
					1, 2, 3  // второй треугольник
			};

			object1.LoadArray(vertices1, sizeof(vertices1) / sizeof(float));
			object1.LoadArrayEBO(indices, sizeof(indices) / sizeof(float));
			object1.AddAtribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));
			object1.Create();
		}

		void ClearBuffers(float r, float g, float b) {
			glClearColor(r, g, b, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void ClearBuffers() {
			glClearColor(0.2, 0.8, 1, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Push() {
			shader.use();
			glBindTexture(GL_TEXTURE_2D, texture1.texture);
			glBindVertexArray(object1.getVAO());
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glFlush();
		}

	};
};