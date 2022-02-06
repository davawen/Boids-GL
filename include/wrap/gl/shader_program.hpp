#pragma once

#include <string>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

		void use();

		GLint get_uniform(const std::string &name) const;

		void set_uniform(const std::string &name, bool value);
		void set_uniform(GLint location, bool value);

		void set_uniform(const std::string &name, GLint value);
		void set_uniform(GLint location, GLint value);

		void set_uniform(const std::string &name, GLfloat value);
		void set_uniform(GLint location, GLfloat value);

		void set_uniform(const std::string &name, const glm::mat4 &value);
		void set_uniform(GLint location, const glm::mat4 &value);
	};
}
