#pragma once
#include <iostream>
#include <GL/glew.h>
#include <vector>

class Object {
public:
	int size;
	int sizeIndec;
	unsigned int VBO, VAO, EBO;
	
	float* vertices;
	unsigned int* indices;

	void Create() {

		float vertices[] = {
			// координаты        // цвета            // текстурные координаты
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхн€€ права€
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижн€€ права€
		   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижн€€ лева€
		   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // верхн€€ лева€ 
		};

		unsigned int indices[] = {  // помните, что мы начинаем с 0!
			0, 1, 3,  // первый треугольник
			1, 2, 3   // второй треугольник
		};
		
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		/*for (int i = 0; i < atrArray.size(); i++) {
			glVertexAttribPointer(atrArray[i].location, atrArray[i].size, GL_FLOAT, GL_FALSE, atrArray[i].stride, (void*)atrArray[i].firststride);
			glEnableVertexAttribArray(atrArray[i].location);
		}*/

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

	void LoadArrayEBO(unsigned int* array, int size) {
		indices = array;
		this->sizeIndec = size;
	}

	void AddAtribute(int location, int size, int stride, int firststride) {
		atrArray.push_back({ location, size, stride,firststride });
	}

private:
	int atributesCount = 0; // the count of atributes. By default 1 
	struct atribute {
		int location, size, stride , firststride;
	};
	std::vector <atribute> atrArray;

};