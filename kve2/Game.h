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
		void start();
		void end();
		bool update(float delta);
		void render();
	};
}