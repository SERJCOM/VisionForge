#pragma once
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "shader.h"


class Window {
public:	
	sf::Window window;

	Window(int sizeX, int sizeY);

	Window();

	void Display();


	int GetWindowWidth();

	int GetWindowHeight();

	bool running = true;

private:
	
	
};
