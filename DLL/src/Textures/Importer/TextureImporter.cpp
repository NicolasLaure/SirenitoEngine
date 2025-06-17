#include "Textures/Importer/TextureImporter.h"
#include "Renderer/Renderer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

TextureImporter::TextureImporter()
{
}

Texture TextureImporter::ImportTexture(const char* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int internalWidth, internalHeight, colorChannels;
	unsigned char* data = stbi_load(path, &internalWidth, &internalHeight, &colorChannels, 0);

	glBindTexture(GL_TEXTURE_2D, textureID);

	GLenum format = GL_RGB;
	switch (colorChannels)
	{
	case 1:
		format = GL_RED;
		glTexImage2D(GL_TEXTURE_2D, 0, format, internalWidth, internalHeight, 0, format, GL_UNSIGNED_BYTE, data);
		break;
	case 2:
		format = GL_RG;
		glTexImage2D(GL_TEXTURE_2D, 0, format, internalWidth, internalHeight, 0, format, GL_UNSIGNED_BYTE, data);
		break;
	case 3:
		format = GL_RGB;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, format, internalWidth, internalHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		break;
	case 4:
		format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, internalWidth, internalHeight, 0, format, GL_UNSIGNED_BYTE, data);
		break;
	default:
		break;
	}

	glGenerateMipmap(GL_TEXTURE_2D);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
	return Texture(textureID, internalWidth, internalHeight);
}

