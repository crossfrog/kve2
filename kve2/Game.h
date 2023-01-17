#pragma once
#include "SpriteBatch.h"

namespace kve {
	class Engine;

	class Game {
	private:
		Engine* engine;

		SpriteBatch spriteBatch;
		Texture* texture1;
		Texture* texture2;

	public:
		void start(Engine* engine);
		void end();
		bool update(float delta);
		void render();
	};
}