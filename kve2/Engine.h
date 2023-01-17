#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "glm/glm.hpp"
#include "Event.h"

namespace kve {
	class Engine {
	private:
		SDL_Window* window;
		SDL_GLContext glContext;

		void end();
		bool update(float delta);
		void render();

	public:
		Event<> startEvent, endEvent, renderEvent;
		Event<float> updateEvent;
		Event<SDL_Event&> keyDownEvent, keyUpEvent;

		void renderClear(glm::vec4 color);

		void start();
	};
}