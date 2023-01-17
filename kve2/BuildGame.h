#pragma once
#include "Game.h"
#include "SpriteBatch.h"
#include "Input.h"

namespace kve {
	enum class InputAction {
		A,
		B,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ACTIONS_COUNT
	};

	class BuildGame : public Game {
	private:
		SpriteBatch spriteBatch;
		Texture* texture1, *texture2;

	public:
		Input<InputAction> input;

		void start() override;
		void end() override;
		void update(float delta) override;
		void render() override;

		BuildGame(Engine& engine) : Game(engine), input(engine) {}
	};
}