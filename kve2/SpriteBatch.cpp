#include "SpriteBatch.h"
#include "Assets.h"

using namespace kve;

GLuint
	SpriteBatch::shaderProgram,
	SpriteBatch::vertexBuffer,
	SpriteBatch::indexBuffer;

void SpriteBatch::startModule() {
	shaderProgram = Assets::createShaderProgram(
		"assets/shaders/vertex.glsl",
		"assets/shaders/fragment.glsl");


}
