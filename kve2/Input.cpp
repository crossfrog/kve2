#include "Input.h"

using namespace kve;

InputState Input::inputState, Input::lastInputState;
std::unordered_map<SDL_Keycode, InputAction> Input::keyActionMap;

std::unordered_map<SDL_Keycode, InputAction> keyActionMap;

bool Input::getActionKeycode(SDL_Event& event, SDL_Keycode& keycode) {
    keycode = event.key.keysym.sym;

    if (keyActionMap.find(keycode) == keyActionMap.end()) {
        return false;
    }

    return true;
}

bool Input::getActionState(InputState state, InputAction action) {
    return state[(int)action];
}

void Input::processKeyDown(SDL_Event& event) {
    SDL_Keycode keycode;

    if (!getActionKeycode(event, keycode)) {
        return;
    }

    inputState[(int)keyActionMap.at(keycode)] = true;
}

void Input::processKeyUp(SDL_Event& event) {
    SDL_Keycode keycode;

    if (!getActionKeycode(event, keycode)) {
        return;
    }

    inputState[(int)keyActionMap.at(keycode)] = false;
}

void Input::addKeyAction(SDL_Keycode keycode, InputAction action) {
    keyActionMap.emplace(keycode, action);
}

bool Input::isActionPressed(InputAction action) {
    return getActionState(inputState, action);
}

bool Input::isActionJustPressed(InputAction action) {
    return getActionState(inputState, action) && !getActionState(lastInputState, action);
}

bool Input::isActionJustReleased(InputAction action) {
    return !getActionState(inputState, action) && getActionState(lastInputState, action);
}

void Input::update() {
    lastInputState = inputState;
}
