#include "TextureImporter.h"
#include "Renderer/Renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

TextureImporter::TextureImporter()
{
}

Texture TextureImporter::ImportTexture(const char* path, int width, int height)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int internalWidth, internalHeight, colorChannels;
	unsigned char* data = stbi_load(path, &internalWidth, &internalHeight, &colorChannels, 0);

	GLenum format = GL_RGB;
	if (colorChannels == 1)
		format = GL_RED;
	else if (colorChannels == 4)
		format = GL_RGBA;

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, internalWidth, internalHeight, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return Texture(textureID, width, height);
}

