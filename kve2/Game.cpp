#include "Game.h"
#include <iostream>
#include "Engine.h"
#include "Assets.h"

using namespace kve;

void Game::start(Engine& engine) {
	texture1 = Assets::loadTexture("assets/textures/test.png");
	texture2 = Assets::loadTexture("assets/textures/test2.png");

	spriteBatch.start();
}

void Game::end(Engine& engine) {
}

bool Game::update(Engine& engine, float delta) {
	std::cout << delta << std::endl;
	return true;
}

void Game::render(Engine& engine) {
	const glm::ivec2 sprites = glm::ivec2(16);
	const glm::vec2 spriteSize = glm::vec2(1.0f) / (glm::vec2)sprites;

	for (int i = 0; i < sprites.y; i++) {
		for (int j = 0; j < sprites.x; j++) {
			Texture* texture = i >= sprites.y / 2 ? texture1 : texture2;

			spriteBatch.drawSprite(
				texture, { (glm::vec2(j, i) * spriteSize - 0.5f) * 2.0f, spriteSize * 2.0f }
			);
		}
	}

	spriteBatch.endBatch();
}
