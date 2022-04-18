#pragma once
#include <iostream>
#include <GL/glew.h>
class Object {
public:
	int size = 0;
	unsigned int VBO, VAO;
	float vertices[9];

	Object() {
		float vertices1[] = {
		-0.5f, -0.5f, 0.0f, // левая вершина
		 0.5f, -0.5f, 0.0f, // правая вершина
		 0.0f,  0.5f, 0.0f  // верхняя вершина   
		};

		for (int i = 0; i < sizeof(vertices1) / sizeof(float); i++) {
			vertices[i] = vertices1[i];
		}
	}

	void Create() {
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


	unsigned int getVBO() {
		return VBO;
	}

	unsigned int getVAO() {
		return VAO;
	}

	/*Object(int size):size(size){
		vertices = new float[size];
	}
	Object(){
		vertices = new float[0];
	}*/
	~Object() {
		/*delete[] vertices;*/
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	float* change_length(float* mapold, int size) {
		std::cout << size << std::endl;
		float* map_t = new float[this->size + size];
		for (int i = 0; i < this->size;i++) {
			map_t[i] = mapold[i];
		}
		this->size += size;
		delete[] vertices;
		return map_t;
	}

	float* return_vert() {
		return vertices;
	}
};