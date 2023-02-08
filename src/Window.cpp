#include "window.h"

Window::Window(int sizeX, int sizeY) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(sizeX, sizeY, " OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
}

Window::Window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1280, 720, " OpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

}

void Window::Display() {
	glfwSwapBuffers(window);
	glfwPollEvents();
}


int Window::GetWindowHeight() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);	
	return height;
}

int Window::GetWindowWidth() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);	
	return width;
}
