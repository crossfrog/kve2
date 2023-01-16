#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Game.h"

namespace kve {
	class Engine {
	private:
		SDL_Window* window = nullptr;
		SDL_GLContext glContext;

		void end();
		bool update(float delta);
		void render();

	public:
		Game game;

		void renderClear(glm::vec4 color);

		void start();
	};
}