#include "wrap/gl/texture.hpp"

namespace gl
{
	Texture::Texture()
	{
		glGenTextures(1, &id);
	}

	Texture::Texture(Target effectiveTarget, GLuint currentBoundTexture)
	{
		glGenTextures(1, &id);

		glBindTexture(effectiveTarget, id);
		glBindTexture(effectiveTarget, currentBoundTexture);
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

	void Texture::bind(Target target, GLenum textureUnit) const
	{
		glActiveTexture(textureUnit);
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

	void Texture::storage_1D(GLint levels, GLint internalFormat, GLsizei width)
	{
		glTextureStorage1D(id, levels, internalFormat, width);
	}
	void Texture::storage_2D(GLint levels, GLint internalFormat, GLsizei width, GLsizei height)
	{
		glTextureStorage2D(id, levels, internalFormat, width, height);
	}
	void Texture::storage_3D(GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth)
	{
		glTextureStorage3D(id, levels, internalFormat, width, height, depth);
	}
	void Texture::storage_2D_multisample(GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
	{
		glTextureStorage2DMultisample(id, samples, internalFormat, width, height, fixedSampleLocations);
	}
	void Texture::storage_3D_multisample(GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
	{
		glTextureStorage3DMultisample(id, samples, internalFormat, width, height, depth, fixedSampleLocations);
	}

	void Texture::texture_view(Target target, const Texture &origTexture, GLint internalFormat, GLuint minLevel, GLuint numLevels, GLuint minLayer, GLuint numLayers)
	{
		glTextureView(id, target, origTexture.get_id(), internalFormat, minLevel, numLevels, minLayer, numLayers);
	}

	void Texture::subimage_1D(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *data)
	{
		glTextureSubImage1D(id, level, xoffset, width, format, type, data);
	}

	void Texture::subimage_2D(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *data)
	{
		glTextureSubImage2D(id, level, xoffset, yoffset, width, height, format, type, data);
	}

	void Texture::subimage_3D(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *data)
	{
		glTextureSubImage3D(id, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	}

	void Texture::generate_mipmap()
	{
		glGenerateTextureMipmap(id);
	}

	void Texture::clear_image(GLint level, GLenum format, GLenum type, const void *data)
	{
		glClearTexImage(id, level, format, type, data);
	}

	void Texture::clear_subimage(GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void *data)
	{
		glClearTexSubImage(id, level, xoffset, 0, 0, width, 1, 1, format, type, data);
	}

	void Texture::clear_subimage(GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void *data)
	{
		glClearTexSubImage(id, level, xoffset, yoffset, 0, width, height, 1, format, type, data);
	}

	void Texture::clear_subimage(GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void *data)
	{
		glClearTexSubImage(id, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
	}
}
