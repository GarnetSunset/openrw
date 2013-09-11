#include <renderwure/render/TextureAtlas.hpp>
#include <algorithm>

TextureAtlas::TextureAtlas(size_t w, size_t h)
	: width(w), height(h), textureName(0), X(0), Y(0), rowHeight(0)
{
	glGenTextures(1, &textureName);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, nullptr
	);
}

TextureAtlas::~TextureAtlas()
{
	glDeleteTextures(1, &textureName);
}

void TextureAtlas::packTexture(uint8_t *data, size_t w, size_t h, float &s, float &t, float &sX, float &sY)
{
	// Ignore null pointer data for testing purposes.
	if( data != nullptr )
	{
		glBindTexture(GL_TEXTURE_2D, textureName);
		glTexSubImage2D(GL_TEXTURE_2D, 0, X, Y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	s = X/(float)width;
	t = Y/(float)height;
	sX = w/(float)width;
	sY = h/(float)height;

	rowHeight = std::max(rowHeight, h);
	X += w;
	if( X >= width ) {
		Y += rowHeight;
		X = rowHeight = 0;
	}
}

bool TextureAtlas::canPack(size_t *w, size_t *h, size_t n) const
{
	size_t rwHeight = rowHeight;
	size_t lX = X, lY = Y;
	for(size_t i = 0; i < n; ++i) {
		lX += (w[i]);
		rwHeight = std::max(rwHeight, h[i]);
		if(lX >= width) {
			lY += rwHeight;
			lX = rwHeight = 0;
		}
	}
	if(lX <= width && lY <= height) {
		return true;
	}
	return false;
}