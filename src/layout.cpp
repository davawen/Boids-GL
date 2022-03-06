#include "layout.hpp"

namespace gl
{
	size_t get_sizeof_type(GLenum type)
	{
		switch(type)
		{
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:
				return sizeof(GLbyte);
			case GL_SHORT:
			case GL_UNSIGNED_SHORT:
				return sizeof(GLshort);
			case GL_INT_2_10_10_10_REV:
			case GL_INT:
			case GL_UNSIGNED_INT_2_10_10_10_REV:
			case GL_UNSIGNED_INT:
				return sizeof(GLint);
			case GL_FLOAT:
				return sizeof(GLfloat);
			case GL_DOUBLE:
				return sizeof(GLdouble);
			case GL_FIXED:
				return sizeof(GLfixed);
			case GL_HALF_FLOAT:
				return sizeof(GLhalf);
		}

		return 0;
	}
}
