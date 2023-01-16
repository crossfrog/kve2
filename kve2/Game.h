#pragma once
#include "SpriteBatch.h"

namespace kve {
	class Engine;

	class Game {
	private:
		SpriteBatch spriteBatch;
		Texture* texture1;
		Texture* texture2;

	public:
		void start(Engine& engine);
		void end(Engine& engine);
		bool update(Engine& engine, float delta);
		void render(Engine& engine);
	};
}