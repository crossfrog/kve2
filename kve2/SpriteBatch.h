#pragma once
#include <glm/glm.hpp>
#include "Rect2.h"
#include "Texture.h"

namespace kve {
	struct SpriteBatchVertex {
		glm::vec3 position;
		glm::vec2 uv;
	};

	class SpriteBatch {
	private:
		static GLuint shaderProgram, vertexBuffer, indexBuffer;

	public:
		static void startModule();

		void drawSprite(Texture* texture, Rect2 rect, Rect2 srcRect);
	};
}