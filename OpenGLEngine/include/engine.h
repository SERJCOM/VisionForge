#pragma once
#include <iostream>
#include "window.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include "object.h"


namespace Engine {
	class Engine: public Camera
	{
	public:
		struct map_color {
			float x, y, z;
		};
		map_color c[3];
		Engine(){
			c[0].x = 1;
			c[0].y = 0;
			c[0].z = 0;

			c[1].x = 0;
			c[1].y = 1;
			c[1].z = 0;

			c[2].x = 0;
			c[2].y = 0;
			c[2].z = 1;

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


		void Push(Object::map_color* map, int size) {
			glPushMatrix();
			glLoadMatrixf(glm::value_ptr(view));

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, map);
			glColorPointer(3, GL_FLOAT, 0, c);
			glDrawArrays(GL_TRIANGLES, 0, size);
			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			//
			glPopMatrix();
			glFlush();
		}
		~Engine(){
			
		}
	private:
		glm::mat4 view;
		int size = 0;
		

	};
}