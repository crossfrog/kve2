#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Game.h"

namespace kve {
	class Engine {
	private:
		static SDL_Window* window;
		static SDL_GLContext glContext;

		static void end();
		static bool update(float delta);
		static void render();

	public:
		static Game game;

		static void renderClear(glm::vec4 color);

		static void start();
	};
}