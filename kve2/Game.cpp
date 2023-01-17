#include "Game.h"
#include <iostream>
#include "Engine.h"
#include "Assets.h"
#include "Input.h"

using namespace kve;

void Game::start() {
	texture1 = Assets::loadTexture("assets/textures/test.png");
	texture2 = Assets::loadTexture("assets/textures/test2.png");

	spriteBatch.start();

	Input::addKeyAction(SDLK_SPACE, InputAction::A);
	Input::addKeyAction(SDLK_a, InputAction::A);
}

void Game::end() {}

bool Game::update(float delta) {
	if (Input::isActionJustPressed(InputAction::A)) {
		std::cout << "pressed" << std::endl;
	}

	return true;
}

void Game::render() {
	Engine::renderClear({ 0.2f, 0.2f, 0.2f, 1.0f });

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
