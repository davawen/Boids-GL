#pragma once

#include <string>
#include <stdexcept>

#include <GL/glew.h>

#include "shader.hpp"

namespace gl
{
	class ShaderProgram
	{
	private:
		unsigned int id;

	public:
		ShaderProgram();
		ShaderProgram(const std::string &vertexSource, const std::string &fragmentSource);

		// Delete copy constructor/assignment
		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram &operator =(const ShaderProgram &) = delete;

		ShaderProgram(ShaderProgram &&other);
		ShaderProgram &operator =(ShaderProgram &&other);

		~ShaderProgram();

		unsigned int get_id() const;

		void attach(Shader &shader);

		// @throws On linking error with the info log
		void link();

		void use() const;

		void set_bool(const std::string &name, bool value) const;
		void set_int(const std::string &name, int value) const;
		void set_float(const std::string &name, float value) const;
	};
}
