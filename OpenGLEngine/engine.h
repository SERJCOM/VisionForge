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
	class Engine: public Camera
	{
	public:
		const char* vert = "../shaders/shader.vert";
		const char* frag = "../shaders/shader.frag";

		Shader shader(vert, frag);

		unsigned int VBO, VAO;
		struct map_color {
			float x, y, z;
		};
		Engine(){
			
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
		-0.5f, -0.5f, 0.0f, // ����� �������
		 0.5f, -0.5f, 0.0f, // ������ �������
		 0.0f,  0.5f, 0.0f  // ������� �������   
			};

			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

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


		void Push(Object::map_color* map, int size) {
			glPushMatrix();
			glLoadMatrixf(glm::value_ptr(view));

			glDepthMask(GL_FALSE);
			

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, map);
			glColorPointer(3, GL_FLOAT, 0, c);
			glDrawArrays(GL_TRIANGLES, 0, size);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			//

			glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBoxID);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glDepthMask(GL_TRUE);

			glPopMatrix();
			glFlush();
		}

	private:
		glm::mat4 view;
		int size = 0;
		

	};
}