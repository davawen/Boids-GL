#include "texture.hpp"

namespace gl
{
	Texture::Texture()
	{
		glGenTextures(1, &id);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &id);
	}

	unsigned int Texture::get_id()
	{
		return id;
	}

	void Texture::bind(Target target)
	{
		glBindTexture(target, id);
	}

	// NOTE: Static function
	void Texture::unbind(Target target)
	{
		glBindTexture(target, 0);
	}

	template <>
	void Texture::set_parameter<GLfloat>(Parameter pname, GLfloat param)
	{
		glTextureParameterf(id, pname, param);
	}

	template <>
	void Texture::set_parameter<GLint>(Parameter pname, GLint param)
	{
		glTextureParameteri(id, pname, param);
	}

	template <>
	void Texture::set_parameter<GLfloat *>(Parameter pname, GLfloat *param)
	{
		glTextureParameterfv(id, pname, param);
	}

	template <>
	void Texture::set_parameter<GLint *>(Parameter pname, GLint *param)
	{
		glTextureParameteriv(id, pname, param);
	}
}
