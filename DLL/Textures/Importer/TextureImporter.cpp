#include "TextureImporter.h"
#include "Renderer/Renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

TextureImporter::TextureImporter()
{
}

unsigned int TextureImporter::ImportTexture(const char* path)
{
	unsigned int texture;
	glGenTextures(1, &texture);

	int width, height, colorChannels;
	unsigned char* data = stbi_load(path, &width, &height, &colorChannels, 0);

	GLenum format = GL_RGB;
	if (colorChannels == 1)
		format = GL_RED;
	else if (colorChannels == 4)
		format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return texture;
}

