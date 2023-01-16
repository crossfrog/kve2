#pragma once
#include <map>
#include <string>
#include "Texture.h"

namespace kve {
	class Assets {
	private:
		static int glSuccess;
		static char glInfoLog[512];

		static std::map<std::string, Texture*> textures;

	public:
		static GLuint loadShader(const char* sourcePath, uint16_t type);
		static GLuint createShaderProgram(const char* vertexSourcePath, const char* fragmentSourcePath);

		static Texture* loadTexture(const char* imagePath);

		static void clear();
		~Assets();
	};
}