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
		Shader shader;
		unsigned int VBO, VAO;

		struct map_color {
			float x, y, z;
		};

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

			float vertices[] = {
		-0.5f, -0.5f, 0.0f, // левая вершина
		 0.5f, -0.5f, 0.0f, // правая вершина
		 0.0f,  0.5f, 0.0f  // верхняя вершина   
			};

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			// Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Вы можете отменить привязку VAO после этого, чтобы другие вызовы VAO случайно не изменили этот VAO (но подобное довольно редко случается).
			// Модификация других VAO требует вызова glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
			glBindVertexArray(0);


		}


		void LoadCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp) {
			view = glm::lookAt(cameraPos, cameraFront + cameraPos, cameraUp);
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
			glBindVertexArray(VAO); // поскольку у нас есть только один VAO, то нет необходимости связывать его каждый раз (но мы сделаем это, чтобы всё было немного организованнее)
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glFlush();
		}

		~Engine() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}

	private:
		glm::mat4 view;
		int size = 0;


	};
}