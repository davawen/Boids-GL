#pragma once

#include <iostream>
#include <stdexcept>

#include <GL/glew.h>

namespace gl
{
	class Shader
	{
	private:
		unsigned int id;

		// Avoid leaking into global namespace and allow convertion to int
		struct _typeContainer
		{
			enum Type
			{
				COMPUTE_SHADER = GL_COMPUTE_SHADER,
				VERTEX_SHADER = GL_VERTEX_SHADER,
				GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
				FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
				TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
				TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER
			};
		};
	
	public:
		using Type = _typeContainer::Type;

		Shader(Type type);

		// Delete copy initialization
		Shader(Shader &) = delete;
		Shader &operator =(Shader &) = delete;

		Shader(Shader &&other);
		Shader &operator =(Shader &&other);

		// Deletes shader (RAII)
		~Shader();

		unsigned int get_id();

		/// @throws On error with the error message
		void compile(const char *source);
		void compile(const std::string &source);
	};
}
