#include "texture.hpp"

namespace gl
{
	Texture::Texture()
	{
		glGenTextures(1, &id);
	}

	Texture::Texture(Texture &&other)
	{
		id = other.id;
		other.id = 0;
	}
	
	Texture &Texture::operator=(Texture &&other)
	{
		if(this != &other)
		{
			glDeleteTextures(1, &id); // Delete current texture

			id = other.id;
			other.id = 0;
		}

		return *this;
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	unsigned int Texture::get_id() const
	{
		return id;
	}

	void Texture::bind(Target target) const
	{
		glBindTexture(target, id);
	}

	// NOTE: Static function
	void Texture::unbind(Target target)
	{
		glBindTexture(target, 0);
	}

	void Texture::set_parameter(Parameter pname, GLfloat param)
	{
		glTextureParameterf(id, pname, param);
	}
	void Texture::set_parameter(Parameter pname, GLint param)
	{
		glTextureParameteri(id, pname, param);
	}
	void Texture::set_parameter(Parameter pname, GLfloat *param)
	{
		glTextureParameterfv(id, pname, param);
	}
	void Texture::set_parameter(Parameter pname, GLint *param)
	{
		glTextureParameteriv(id, pname, param);
	}

	void Texture::storage1D(GLint levels, GLint internalFormat, GLsizei width)
	{
		glTextureStorage1D(id, levels, internalFormat, width);
	}
	void Texture::storage2D(GLint levels, GLint internalFormat, GLsizei width, GLsizei height)
	{
		glTextureStorage2D(id, levels, internalFormat, width, height);
	}
	void Texture::storage3D(GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth)
	{
		glTextureStorage3D(id, levels, internalFormat, width, height, depth);
	}
	void Texture::storage2DMultisample(GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
	{
		glTextureStorage2DMultisample(id, samples, internalFormat, width, height, fixedSampleLocations);
	}
	void Texture::storage3DMultisample(GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
	{
		glTextureStorage3DMultisample(id, samples, internalFormat, width, height, depth, fixedSampleLocations);
	}

	void Texture::textureView(Target target, const Texture &origTexture, GLint internalFormat, GLuint minLevel, GLuint numLevels, GLuint minLayer, GLuint numLayers)
	{
		glTextureView(id, target, origTexture.get_id(), internalFormat, minLevel, numLevels, minLayer, numLayers);
	}

	// void Texture::image2D()
	// {;
	// 	glTexImage2D()
	// 	
	// }
}
