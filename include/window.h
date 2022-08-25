#pragma once
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>



class Window {
public:
	sf::Window window;

	Window(int sizeX, int sizeY);

	Window();

	void Display();

	float GetWindowWidth();

	float GetWindowHeight();

	bool running = true;
};
