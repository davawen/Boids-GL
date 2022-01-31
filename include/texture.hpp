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
				TEXTURE_1D = GL_TEXTURE_1D,
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
		
		Texture(Texture &) = delete;
		Texture &operator =(Texture &) = delete;

		Texture(Texture &&other);
		Texture &operator =(Texture &&other);

		~Texture();

		unsigned int get_id() const;

		void bind(Target target) const;
		static void unbind(Target target);

		void set_parameter(Parameter pname, GLfloat param);
		void set_parameter(Parameter pname, GLint param);
		void set_parameter(Parameter pname, GLfloat *param);
		void set_parameter(Parameter pname, GLint *param);
		
		/// Allocates 1 dimensional immutable storage
		/// Effective target of the texture must be Target::TEXTURE_1D
		void storage1D(GLint levels, GLint internalFormat, GLsizei width); 
		/// Allocates 2 dimensional immutable storage
		/// Effective target of the texture must be one of Target::TEXTURE_2D, Target::TEXTURE_RECTANGLE, Target::TEXTURE_CUBE_MAP or Target::TEXTURE_1D_ARRAY
		void storage2D(GLint levels, GLint internalFormat, GLsizei width, GLsizei height);
		/// Allocates 3 dimensional immutable storage
		/// Effective target of the texture must be one of Target::TEXTURE_3D, Target::TEXTURE_2D_ARRAY, Target::TEXTURE_CUBE_MAP_ARRAY
		void storage3D(GLint levels, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth);

		/// Effective target of the texture must be Target::TEXTURE_2D_MULTISAMPLE
		void storage2DMultisample( GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations );
		/// Effective target of the texture must be Target::TEXTURE_2D_MULTISAMPLE_ARRAY
		void storage3DMultisample( GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations );

		/// Creates a view on previously-created storage by another texture as this texture's storage
		/// @param minLevel Specifies the mipmap level in the origTexture that will become the base level of the view texture
		/// @param numLevels Specifies how many mipmaps are to be viewed
		/// @param minLayer Used by textures which have layers or faces ( Target::TEXTURE_1D_ARRAY, Target::TEXTURE_2D_ARRAY, Target::TEXTURE_CUBE_MAP, Target::TEXTURE_CUBE_MAP_ARRAY ) similarly to minLevel
		/// @param numLayers Used by textures which have layers or faces similarly to numLevels
		void textureView(Target target, const Texture &origTexture, GLint internalFormat, GLuint minLevel, GLuint numLevels, GLuint minLayer, GLuint numLayers);

		// void image2D();

	private:
		unsigned int id;
	};
}
