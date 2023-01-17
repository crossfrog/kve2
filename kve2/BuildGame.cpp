#include "BuildGame.h"
#include <iostream>
#include "Assets.h"

using namespace kve;

void BuildGame::start() {
	texture1 = Assets::loadTexture("assets/textures/test.png");
	texture2 = Assets::loadTexture("assets/textures/test2.png");

	spriteBatch.start();

	input.addKeyAction(SDLK_SPACE, InputAction::A);
	input.addKeyAction(SDLK_a, InputAction::A);
}

void BuildGame::end() {}

void BuildGame::update(float delta) {
	if (input.isActionJustPressed(InputAction::A)) {
		std::cout << "hi" << std::endl;
	}
}

void BuildGame::render() {
	engine->renderClear({ 0.2f, 0.2f, 0.2f, 1.0f });

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