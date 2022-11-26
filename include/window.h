#pragma once
#include <iostream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "shader.h"


class Window {
public:	

	GLFWwindow* window;

	Window(int sizeX, int sizeY);

	Window();

	void Display();

	int GetWindowWidth();

	int GetWindowHeight();

	bool running = true;

private:
	
	
};
