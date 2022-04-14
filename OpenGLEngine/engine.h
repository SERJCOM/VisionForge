#pragma once
#include <iostream>
#include "window.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"


namespace Engine {
	class Engine: public Camera
	{
	public:
		struct map_color {
			float x, y, z;
		};
		Engine(){
			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glClearDepth(1.f);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum(-1, 1, -1, 1, 1, 5000);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
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

		void LoadMapMemory(map_color* map_t, int size) {
			map = map_t;
			this->size = size;
		}

		void Push() {
			glPushMatrix();
			glLoadMatrixf(glm::value_ptr(view));

			glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, map);
			glDrawArrays(GL_TRIANGLES, 0, size);
			glDisableClientState(GL_VERTEX_ARRAY);

			glPopMatrix();
			glFlush();
		}
		~Engine(){
			delete[] map;
		}
	private:
		glm::mat4 view;
		map_color* map;
		int size = 0;
	};
}