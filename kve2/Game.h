#pragma once
#include "Engine.h"

namespace kve {
	class Game {
	private:
		EventHandler<>* startEvent, *endEvent, *renderEvent;
		EventHandler<float>* updateEvent;

	protected:
		Engine* engine;

	public:
		virtual void start() {}
		virtual void end() {}
		virtual void update(float delta) {}
		virtual void render() {}

		Game(Engine& engine);
		~Game();
	};
}