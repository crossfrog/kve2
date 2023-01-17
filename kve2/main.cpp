#define SDL_MAIN_HANDLED
#include "Engine.h"
#include "BuildGame.h"

int main() {
	kve::Engine engine;
	kve::BuildGame game(engine);

	engine.start();

	return 0;
}