#pragma once
#include <iostream>
#include <GL/glew.h>
#include "SFML/Window/Window.hpp"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include "VisionForge/System/Shader.hpp"


namespace lthm{

class Window: public sf::Window {
public:	

	Window(int x, int y){
        this->setSize(sf::Vector2u{x, y});
        
    }

    using sf::Window::Window;

private:
	
	
};


}