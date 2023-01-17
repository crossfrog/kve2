#pragma once
#include <array>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "Engine.h"

namespace kve {
	template<typename ActionsEnum>
	class Input {
	private:
		Engine* engine;

		using InputState = std::array<bool, (int)ActionsEnum::ACTIONS_COUNT>;

		InputState inputState, lastInputState;

		std::unordered_map<SDL_Keycode, ActionsEnum> keyActionMap;

		EventHandler<SDL_Event&>* keyDownEvent, *keyUpEvent;
		EventHandler<float>* updateEvent;

		bool getActionKeycode(SDL_Event& event, SDL_Keycode& keycode) {
			keycode = event.key.keysym.sym;

			if (keyActionMap.find(keycode) == keyActionMap.end()) {
				return false;
			}

			return true;
		}

		bool getActionState(InputState state, ActionsEnum action) {
			return state[(int)action];
		}

		void processKeyDown(SDL_Event& event) {
			SDL_Keycode keycode;

			if (!getActionKeycode(event, keycode)) {
				return;
			}

			inputState[(int)keyActionMap.at(keycode)] = true;
		}

		void processKeyUp(SDL_Event& event) {
			SDL_Keycode keycode;

			if (!getActionKeycode(event, keycode)) {
				return;
			}

			inputState[(int)keyActionMap.at(keycode)] = false;
		}

		void update(float delta) {
			lastInputState = inputState;
		}

	public:
		void addKeyAction(SDL_Keycode keycode, ActionsEnum action) {
			keyActionMap.emplace(keycode, action);
		}

		bool isActionPressed(ActionsEnum action) {
			return getActionState(inputState, action);
		}

		bool isActionJustPressed(ActionsEnum action) {
			return getActionState(inputState, action) && !getActionState(lastInputState, action);
		}

		bool isActionJustReleased(ActionsEnum action) {
			return !getActionState(inputState, action) && getActionState(lastInputState, action);
		}

		Input(Engine& engine) {
			this->engine = &engine;

			keyDownEvent = engine.keyDownEvent += std::bind(&Input::processKeyDown, this, std::placeholders::_1);
			keyUpEvent = engine.keyUpEvent += std::bind(&Input::processKeyUp, this, std::placeholders::_1);
			updateEvent = engine.updateEvent += std::bind(&Input::update, this, std::placeholders::_1);
		}

		~Input() {
			engine->keyDownEvent -= keyDownEvent;
			engine->keyUpEvent -= keyUpEvent;
			engine->updateEvent -= updateEvent;
		}
	};
}