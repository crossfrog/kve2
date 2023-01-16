#include "SpriteBatch.h"
#include "Assets.h"

using namespace kve;

void SpriteBatch::renderBatch(int spriteCount, Texture* texture) {
	glBindVertexArray(vertexArray);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpriteBatchVertex) * spriteCount * 4, vertices, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getGlTexture());

	glUseProgram(shaderProgram);

	glDrawElements(GL_TRIANGLES, spriteCount * 6, GL_UNSIGNED_INT, 0);
}

void SpriteBatch::drawSprite(
	Texture* texture,
	Rect2 rect,
	Rect2 sourceRect,
	glm::vec4 color
) {
	batchedSprites.push_back(
		{ texture, rect, sourceRect, color }
	);
}

void SpriteBatch::endBatch() {
	if (batchedSprites.size() == 0) {
		return;
	}

	Texture* currentTexture = batchedSprites[0].texture;
	int spriteCount = 0;

	for (BatchedSprite& batchedSprite : batchedSprites) {
		if (batchedSprite.texture != currentTexture ||
			spriteCount >= batchSize) {

			renderBatch(spriteCount, currentTexture);

			currentTexture = batchedSprite.texture;
			spriteCount = 0;
		}

		int startVertex = spriteCount * 4;

		SpriteBatchVertex* vertex1 = &vertices[startVertex + 0];
		SpriteBatchVertex* vertex2 = &vertices[startVertex + 1];
		SpriteBatchVertex* vertex3 = &vertices[startVertex + 2];
		SpriteBatchVertex* vertex4 = &vertices[startVertex + 3];

		glm::vec2 start = batchedSprite.rect.position;
		glm::vec2 end = start + batchedSprite.rect.size;

		vertex1->position = glm::vec3(start, 0.0f);
		vertex2->position = glm::vec3(end.x, start.y, 0.0f);
		vertex3->position = glm::vec3(start.x, end.y, 0.0f);
		vertex4->position = glm::vec3(end, 0.0f);

		glm::vec2 sourceStart = batchedSprite.sourceRect.position;
		glm::vec2 sourceEnd = sourceStart + batchedSprite.sourceRect.size;

		vertex1->uv = glm::vec3(sourceStart, 0.0f);
		vertex2->uv = glm::vec3(sourceEnd.x, sourceStart.y, 0.0f);
		vertex3->uv = glm::vec3(sourceStart.x, sourceEnd.y, 0.0f);
		vertex4->uv = glm::vec3(sourceEnd, 0.0f);

		vertex1->color = vertex2->color = vertex3->color = vertex4->color =
			batchedSprite.color;

		spriteCount++;
	}

	if (spriteCount > 0) {
		renderBatch(spriteCount, currentTexture);
	}

	batchedSprites.clear();
}

void SpriteBatch::start() {
	shaderProgram = Assets::createShaderProgram(
		"assets/shaders/vertex.glsl",
		"assets/shaders/fragment.glsl");

	// Create vertex array
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Create vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(SpriteBatchVertex),
		(void*)offsetof(SpriteBatchVertex, position));

	glEnableVertexAttribArray(0);

	// UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(SpriteBatchVertex),
		(void*)offsetof(SpriteBatchVertex, uv));

	glEnableVertexAttribArray(1);

	// Color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE,
		sizeof(SpriteBatchVertex),
		(void*)offsetof(SpriteBatchVertex, color));

	glEnableVertexAttribArray(2);

	// Create index buffer
	unsigned int indices[batchSize * 6]{};

	for (int i = 0; i < batchSize; i++) {
		int startIndex = i * 6;
		int startVertex = i * 4;

		// First triangle
		indices[startIndex + 0] = startVertex + 0;
		indices[startIndex + 1] = startVertex + 1;
		indices[startIndex + 2] = startVertex + 2;

		// Second triangle
		indices[startIndex + 3] = startVertex + 1;
		indices[startIndex + 4] = startVertex + 2;
		indices[startIndex + 5] = startVertex + 3;
	}

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

SpriteBatch::~SpriteBatch() {
	glDeleteProgram(shaderProgram);

	glDeleteVertexArrays(1, &vertexArray);

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
}
