#include "Engine.h"
#include <iostream>
#include "Assets.h"

using namespace kve;

void Engine::end() {
	game.end(*this);

	Assets::clear();

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Engine::update(float delta) {
	static SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return false;
		}
	}

	if (!game.update(*this, delta)) {
		return false;
	}

	render();
	return true;
}

void Engine::render() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	game.render(*this);

	SDL_GL_SwapWindow(window);
}

void Engine::start() {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(
		"Test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_OPENGL);

	if (!window) {
		std::cerr << "Failed to initialize SDL window." << std::endl;
		return;
	}

	glContext = SDL_GL_CreateContext(window);

	GLenum glewError = glewInit();

	if (glewError != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW:\n" << glewGetErrorString(glewError) << std::endl;
	}

	game.start(*this);

	while (true) {
		static Uint32 lastTime = 0;
		
		Uint32 currentTime = SDL_GetTicks();
		Uint32 delta = currentTime - lastTime;

		if (!update((float)delta / 1000.0f)) {
			break;
		}

		SDL_Delay(std::max((1000 / 60) - (int)(SDL_GetTicks() - currentTime), 0));
		lastTime = currentTime;
	}

	end();
}