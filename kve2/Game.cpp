#include "Game.h"

using namespace kve;

Game::Game(Engine& engine) {
	this->engine = &engine;

	startEvent = engine.startEvent += std::bind(&Game::start, this);
	endEvent = engine.endEvent += std::bind(&Game::end, this);
	updateEvent = engine.updateEvent += std::bind(&Game::update, this, std::placeholders::_1);
	renderEvent = engine.renderEvent += std::bind(&Game::render, this);
}

Game::~Game() {
	engine->startEvent -= startEvent;
	engine->endEvent -= endEvent;
	engine->updateEvent -= updateEvent;
	engine->renderEvent -= renderEvent;
}