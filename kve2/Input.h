#pragma once
#include <array>
#include <unordered_map>
#include <SDL2/SDL.h>

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

	using InputState = std::array<bool, (int)InputAction::ACTIONS_COUNT>;

	class Input {
	private:
		static InputState inputState, lastInputState;

		static std::unordered_map<SDL_Keycode, InputAction> keyActionMap;

		static bool getActionKeycode(SDL_Event& event, SDL_Keycode& keycode);
		static bool getActionState(InputState state, InputAction action);

		static void processKeyDown(SDL_Event& event);
		static void processKeyUp(SDL_Event& event);

		static void update();

		friend class Engine;

	public:
		static void addKeyAction(SDL_Keycode keycode, InputAction action);

		static bool isActionPressed(InputAction action);
		static bool isActionJustPressed(InputAction action);
		static bool isActionJustReleased(InputAction action);
	};
}