#include "wrap/gl/shader.hpp"

namespace gl
{
	Shader::Shader(Shader::Type type)
	{
		id = glCreateShader(type);
	}

	Shader::Shader(Shader &&other)
	{
		id = other.id;
		other.id = 0;
	}

	Shader &Shader::operator =(Shader &&other)
	{
		if(this != &other)
		{
			glDeleteShader(id); // Free up current program

			id = other.id;
			other.id = 0;
		}

		return *this;
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
