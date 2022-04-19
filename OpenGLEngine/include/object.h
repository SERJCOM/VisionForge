#pragma once
#include <iostream>
#include <GL/glew.h>
class Object {
public:
	int size;
	unsigned int VBO, VAO;
	
	float* vertices;

	
	/*Object() {
		vertices = new float[0];
		size = sizeof(vertices) / sizeof(float);
		std::cout << size << std::endl;
	}*/

	void Create() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);

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

	~Object() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void LoadArray(float* array, int size) {
		vertices = array;
		this->size = size;
	}

	/*float* change_length(int size) {
		if (size <= this->size) {
			return vertices;
		}
		float* pNewArray = new float[size];
		std::cout << "new sizew: " << sizeof(vertices) / sizeof(float) << std::endl;
		memcpy(pNewArray, vertices, sizeof(float) * this->size);
		std::cout << "new size0: " << sizeof(pNewArray) / sizeof(float) << std::endl;
		delete[] vertices;
		this->size = size;
		return pNewArray;
	}

	void LoadArray(float* array, int size) {
		int sizeold = this->size;
		std::cout << "the old size: " << sizeold << std::endl;
		vertices = change_length(size);
		if (size < sizeold) {
			for (int i = 0; i < size; i++) {
				vertices[i] = array[i];
			}
		}
		else {
			memcpy(vertices, array, 36);
			std::cout << "new size: " << sizeof(vertices) / sizeof(float) << std::endl;
		}
	}*/

	float* return_vert() {
		return vertices;
	}
};