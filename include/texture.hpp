#pragma once

#include <GL/glew.h>

namespace gl
{
	class Texture
	{
	private:
		struct _enumContainer
		{
			enum Target
			{
				TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
				TEXTURE_2D = GL_TEXTURE_2D,
				TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
				TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
				TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
				TEXTURE_3D = GL_TEXTURE_3D,
				TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
				TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
				TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE
			};

			enum Parameter
			{
				DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
				BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
				COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
				COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
				LOD_BIAS = GL_TEXTURE_LOD_BIAS,
				MIN_FILTER = GL_TEXTURE_MIN_FILTER,
				MAG_FILTER = GL_TEXTURE_MAG_FILTER,
				MIN_LOD = GL_TEXTURE_MIN_LOD,
				MAX_LOD = GL_TEXTURE_MAX_LOD,
				MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
				SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
				SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
				SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
				SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
				WRAP_S = GL_TEXTURE_WRAP_S,
				WRAP_T = GL_TEXTURE_WRAP_T,
				WRAP_R = GL_TEXTURE_WRAP_R
			};
		};

	public:
		using Target = _enumContainer::Target;
		using Parameter = _enumContainer::Parameter;

		Texture();
		~Texture();

		unsigned int get_id();

		void bind(Target target);
		static void unbind(Target target);

		template <typename T>
		void set_parameter(Parameter pname, T param);

		template <>
		void set_parameter<GLfloat>(Parameter pname, GLfloat param);
		template <>
		void set_parameter<GLint>(Parameter pname, GLint param);
		template <>
		void set_parameter<GLfloat *>(Parameter pname, GLfloat *param);
		template <>
		void set_parameter<GLint *>(Parameter pname, GLint *param);

	private:
		unsigned int id;
	};
}
