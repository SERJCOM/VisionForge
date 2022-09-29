#include "engine.h"

Engine::Engine() {
	glewInit();
	glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_DEPTH_TEST);
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
}

void Engine::ClearBuffers() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

