#include "Game.h"
#include <iostream>
#include "Engine.h"
#include "SpriteBatch.h"

using namespace kve;

void Game::start(Engine& engine) {
	SpriteBatch::startModule();
}

void Game::end(Engine& engine) {
}

bool Game::update(Engine& engine, float delta) {
	std::cout << delta << std::endl;
	return true;
}

void Game::render(Engine& engine) {
}
