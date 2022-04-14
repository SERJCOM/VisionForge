#pragma once
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace Engine {
	class Window {
	public:
		sf::Window window;
		Window(int sizeX, int sizeY) {
			window.create(sf::VideoMode(sizeX, sizeY), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
			window.setVerticalSyncEnabled(true);
			window.setActive(true);
	
		}
		Window() {
			window.create(sf::VideoMode(720, 1280), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
			window.setVerticalSyncEnabled(true);
			window.setActive(true);
		}
		void Display() {
			window.display();
		}
		
	};
}