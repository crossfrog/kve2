#pragma once
#include <GL/glew.h>

namespace kve {
	class Texture {
	private:
		GLuint glTexture;

		friend class Assets;

	public:
		GLuint getGlTexture();
	};
}