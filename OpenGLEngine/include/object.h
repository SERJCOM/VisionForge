#pragma once
#include <iostream>
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object {
public:
	int size;
	int sizeIndec;
	unsigned int VBO, VAO;

	float* vertices;
	unsigned int* indices;

	int stride = 6;

	void Create() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);


		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		for (int i = 0; i < atrArray.size(); i++) {
			glVertexAttribPointer(atrArray[i].location, atrArray[i].size, GL_FLOAT, GL_FALSE, atrArray[i].stride, (void*)atrArray[i].firststride);
			glEnableVertexAttribArray(atrArray[i].location);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

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

	void SetWidthHeight(float& width, float& height) {
		this->width = width;
		this->height = height;
	}

	glm::mat4 modelMatrix(float x, float y, float z, float angle) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y, z));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));

		return model;
	}

	glm::mat4 viewMatrix(float x, float y, float z) {
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(x, y, z));
		return view;
	}

	glm::mat4 projectionMatrix() {
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		return projection;
	}

	void SetMatrixShader(glm::mat4 model, glm::mat4 view, glm::mat4 projection, unsigned int ID) {
		int modelLoc = glGetUniformLocation(ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void SetMatrixShader(glm::mat4 view, glm::mat4 projection, unsigned int ID) {
		int viewLoc = glGetUniformLocation(ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void SetTextureMode(bool flag, unsigned int ID) {
		glUniform1d(glGetUniformLocation(ID, "texturePermit"), flag);
	}

	void SetBasicColor(unsigned int ID) {
		glm::vec3 color = glm::vec3(1.0f, 0.5f, 0.3f);
		glUniform3f(glGetUniformLocation(ID, "lightColor"), 0.3f, 0.5f, 0.9f);
	}



private:
	int atributesCount = 0; // the count of atributes. By default 1 
	struct atribute {
		int location, size, stride, firststride;
	};
	std::vector <atribute> atrArray;
	float width, height;



};