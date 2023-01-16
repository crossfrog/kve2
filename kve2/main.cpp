#define SDL_MAIN_HANDLED
#include "Engine.h"

int main() {
	kve::Engine engine{};
	engine.start();

	return 0;
}