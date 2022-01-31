#include "shader_program.hpp"

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

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(id);
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

	void ShaderProgram::use() const
	{
		glUseProgram(id);
	}

	void ShaderProgram::set_bool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}

	void ShaderProgram::set_int(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void ShaderProgram::set_float(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}
}
