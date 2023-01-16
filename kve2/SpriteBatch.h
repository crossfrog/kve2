#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Rect2.h"
#include "Texture.h"

namespace kve {
	struct SpriteBatchVertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec4 color;
	};

	struct BatchedSprite {
		Texture* texture;
		Rect2 rect, sourceRect;
		glm::vec4 color;
	};

	class SpriteBatch {
	private:
		static constexpr int batchSize = 1024;

		GLuint shaderProgram, vertexArray, vertexBuffer, indexBuffer;
		std::vector<BatchedSprite> batchedSprites;

		SpriteBatchVertex vertices[batchSize * 4];

		void renderBatch(int spriteCount, Texture* texture);

	public:
		void drawSprite(
			Texture* texture,
			Rect2 rect,
			Rect2 sourceRect = { glm::vec2(0.0f), glm::vec2(1.0f) },
			glm::vec4 color = glm::vec4(1.0f)
		);

		void endBatch();

		void start();
		~SpriteBatch();
	};
}