#include "Assets.h"
#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>

using namespace kve;

int Assets::glSuccess;
char Assets::glInfoLog[512];

std::map<std::string, Texture*> Assets::textures;

GLuint Assets::loadShader(const char* sourcePath, uint16_t type) {
	GLuint shader = glCreateShader(type);

	std::ifstream srcStream(sourcePath);

	if (!srcStream.is_open()) {
		std::cerr << "Shader at path \"" << sourcePath << "\" could not be loaded." << std::endl;
		return shader;
	}

	std::string srcText, srcLine;

	while (std::getline(srcStream, srcLine)) {
		srcText += srcLine + "\n";
	}

	const char* sourceCStr = srcText.c_str();

	glShaderSource(shader, 1, &sourceCStr, NULL);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &glSuccess);

	if (!glSuccess) {
		glGetShaderInfoLog(shader, sizeof(glInfoLog), NULL, glInfoLog);

		std::cerr << "Shader compilation failed:" << std::endl;
		std::cerr << glInfoLog << std::endl;
	}

	return shader;
}

GLuint Assets::createShaderProgram(const char* vertexSourcePath, const char* fragmentSourcePath) {
	GLuint vertexShader, fragmentShader;

	vertexShader = Assets::loadShader(vertexSourcePath, GL_VERTEX_SHADER);
	fragmentShader = Assets::loadShader(fragmentSourcePath, GL_FRAGMENT_SHADER);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &glSuccess);

	if (!glSuccess) {
		glGetProgramInfoLog(shaderProgram, sizeof(glInfoLog), NULL, glInfoLog);

		std::cerr << "Shader program linkage failed:" << std::endl;
		std::cerr << glInfoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

Texture* Assets::loadTexture(const char* imagePath) {
	if (textures.find(imagePath) == textures.end()) {
		Texture* texture = new Texture;

		glGenTextures(1, &texture->glTexture);
		glBindTexture(GL_TEXTURE_2D, texture->glTexture);

		SDL_Surface* imgSurface = IMG_Load(imagePath);

		if (!imgSurface) {
			std::cerr << "Image at path \"" << imagePath << "\" could not be loaded." << std::endl;
			return nullptr;
		}

		glTexImage2D(
			GL_TEXTURE_2D, 0, 3,
			imgSurface->w, imgSurface->h,
			0, GL_RGB, GL_UNSIGNED_BYTE,
			imgSurface->pixels);

		SDL_FreeSurface(imgSurface);

		textures.emplace(imagePath, texture);
		return texture;
	}
	else {
		return textures.at(imagePath);
	}
}

void Assets::clear() {
	for (auto& strTexPair : textures) {
		Texture* texture = strTexPair.second;
		
		glDeleteTextures(1, &texture->glTexture);
		delete texture;
	}

	textures.clear();
}

Assets::~Assets() {
	clear();
}
