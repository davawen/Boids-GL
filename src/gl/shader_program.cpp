#include "wrap/gl/shader_program.hpp"

namespace gl
{
	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
	}

	ShaderProgram::ShaderProgram(const std::string &vertexSource, const std::string &fragmentSource)
	{
		id = glCreateProgram();

		Shader vertexShader(Shader::Type::VERTEX_SHADER);
		vertexShader.compile(vertexSource);

		Shader fragmentShader(Shader::Type::FRAGMENT_SHADER);
		fragmentShader.compile(fragmentSource);

		attach(vertexShader);
		attach(fragmentShader);

		link();
	}

	ShaderProgram::ShaderProgram(ShaderProgram &&other)
	{
		id = other.id;
		other.id = 0;
	}

	ShaderProgram &ShaderProgram::operator =(ShaderProgram &&other)
	{
		if(this != &other)
		{
			glDeleteProgram(id); // Free up current program

			id = other.id;
			other.id = 0;
		}

		return *this;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(id);
		id = 0;
	}

	unsigned int ShaderProgram::get_id() const
	{
		return id;
	}

	void ShaderProgram::attach(Shader &shader)
	{
		glAttachShader(id, shader.get_id());
	}

	void ShaderProgram::link()
	{
		glLinkProgram(id);

		int success;
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if(!success)
		{
			char infoLog[1024];
			glGetProgramInfoLog(id, 1024, NULL, infoLog);

			printf("Error linking shader program %u.\n", id);

			throw std::runtime_error(infoLog);
		}
	}

	void ShaderProgram::use()
	{
		glUseProgram(id);
	}

	GLint ShaderProgram::get_uniform(const std::string &name) const
	{
		return glGetUniformLocation(id, name.c_str());
	}

	void ShaderProgram::set_uniform(const std::string &name, bool value)
	{
		glUniform1i(get_uniform(name), (int)value);
	}

	void ShaderProgram::set_uniform(GLint location, bool value)
	{
		glUniform1i(location, (int)value);
	}

	void ShaderProgram::set_uniform(const std::string &name, GLint value)
	{
		glUniform1i(get_uniform(name), value);
	}

	void ShaderProgram::set_uniform(GLint location, GLint value)
	{
		glUniform1i(location, value);
	}

	void ShaderProgram::set_uniform(const std::string &name, GLfloat value)
	{
		glUniform1f(get_uniform(name), value);
	}

	void ShaderProgram::set_uniform(GLint location, GLfloat value)
	{
		glUniform1f(location, value);
	}

	void ShaderProgram::set_uniform(const std::string &name, const glm::mat4 &value)
	{
		glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::set_uniform(GLint location, const glm::mat4 &value)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}
