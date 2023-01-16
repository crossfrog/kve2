#pragma once

namespace kve {
	class Engine;

	class Game {
	public:
		void start(Engine& engine);
		void end(Engine& engine);
		bool update(Engine& engine, float delta);
		void render(Engine& engine);
	};
}