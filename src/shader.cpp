#include "shader.hpp"

namespace gl
{
	Shader::Shader(Shader::Type type)
	{
		id = glCreateShader(type);
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
	}

	void Shader::compile(const char *source)
	{
		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			char infoLog[1024];
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			
			printf("Error compiling shader %u\nSource: {\n%s\n}\n", id, source);

			throw std::runtime_error(infoLog);
		}
	}

	void Shader::compile(const std::string &source)
	{
		compile(source.c_str());
	}

	unsigned int Shader::get_id()
	{
		return id;
	}
}
