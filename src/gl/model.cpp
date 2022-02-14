#include "wrap/gl/model.hpp"

namespace gl
{
	Model::Model(GLfloat *vertices, size_t numVertices, GLenum usage, const Layout &layout)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		EBO = 0;

		this->numVertices = numVertices;
		this->numIndices = 0;

		glBindVertexArray(VAO); // bind()
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, numVertices * layout.stride, vertices, usage);

		for(auto &optAttribute : layout.attributes)
		{
			if(!optAttribute.has_value()) continue;

			auto &attribute = optAttribute.value();
			set_vertex_attribute(attribute.index, attribute.size, attribute.type, layout.stride, attribute.offset, attribute.normalized);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0); // unbind()
	}

	Model::Model(GLfloat *vertices, size_t numVertices, GLuint *indices, size_t numIndices, GLenum usage, const Layout &layout)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		this->numVertices = numVertices;
		this->numIndices = numIndices;

		glBindVertexArray(VAO); // bind()
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ARRAY_BUFFER, numVertices * layout.stride, vertices, usage);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLint), indices, usage);

		for(auto &optAttribute : layout.attributes)
		{
			if(!optAttribute.has_value()) continue;

			auto &attribute = optAttribute.value();
			set_vertex_attribute(attribute.index, attribute.size, attribute.type, layout.stride, attribute.offset, attribute.normalized);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0); // unbind()

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind index buffer after array buffer to avoid resetting it in the array buffer
	}

	Model::Model(Model &&other)
	{
		VAO = other.VAO;
		VBO = other.VBO;
		EBO = other.EBO;

		numVertices = other.numVertices;
		numIndices = other.numIndices;

		other.VAO = 0;
		other.VBO = 0;
		other.EBO = 0;

		other.numVertices = 0;
		other.numIndices = 0;
	}

	Model &Model::operator=(Model &&other)
	{
		if(&other != this)
		{
			free();

			VAO = other.VAO;
			VBO = other.VBO;
			EBO = other.EBO;

			numVertices = other.numVertices;
			numIndices = other.numIndices;

			other.VAO = 0;
			other.VBO = 0;
			other.EBO = 0;

			other.numVertices = 0;
			other.numIndices = 0;
		}

		return *this;
	}

	Model::~Model()
	{
		free();
	}

	void Model::free()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Model::bind()
	{
		glBindVertexArray(VAO);
	}

	void Model::unbind()
	{
		glBindVertexArray(0);
	}

	void Model::set_vertex_attribute(GLuint layout, GLint size, GLenum type, GLsizei stride, size_t offset, GLboolean normalized)
	{
		glVertexAttribPointer(layout, size, type, normalized, stride, (void *)offset);
		glEnableVertexAttribArray(layout);
	}

	void Model::draw(GLenum mode) const {
		if(EBO == 0) glDrawArrays(mode, 0, numVertices);
		else glDrawElements(mode, numIndices, GL_UNSIGNED_INT, nullptr);
	}

	void Model::draw(GLenum mode, GLint first, GLsizei count) const
	{
		if(EBO == 0) glDrawArrays(mode, first, count);
		else glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
	}

	GLuint Model::get_vao() const
	{
		return VAO;
	}

	GLuint Model::get_vbo() const
	{
		return VBO;
	}

	GLuint Model::get_ebo() const
	{
		return EBO;
	}
}
