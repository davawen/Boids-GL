#include "wrap/gl/model.hpp"
#include "wrap/gl/buffer.hpp"
#include <utility>

namespace gl
{
	Model::Model()
	{
		glGenVertexArrays(1, &VAO);

		VBO = nullptr;
		this->numVertices = 0;

		EBO = nullptr;
		this->numIndices = 0;
	}

	Model::Model(VertexBuffer *vertexBuffer, size_t numVertices, const VertexDescriptor &layout)
	{
		glGenVertexArrays(1, &VAO);

		EBO = nullptr;
		this->numIndices = 0;

		bind();
		
		set_vbo(vertexBuffer, numVertices, layout);

		unbind();
	}

	Model::Model(VertexBuffer *vertexBuffer, size_t numVertices, IndexBuffer *indexBuffer, size_t numIndices, const VertexDescriptor &layout)
	{
		glGenVertexArrays(1, &VAO);

		bind();
		
		set_vbo(vertexBuffer, numVertices, layout);

		set_ebo(indexBuffer, numIndices);

		unbind();

	}

	Model::Model(Model &&other)
	{
		VAO = other.VAO;
		VBO = other.VBO;
		EBO = other.EBO;

		numVertices = other.numVertices;
		numIndices = other.numIndices;

		other.VAO = 0;
		other.VBO = nullptr;
		other.EBO = nullptr;

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
			other.VBO = nullptr;
			other.EBO = nullptr;

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

	void Model::draw(GLenum mode) const
	{
		if(EBO == nullptr) glDrawArrays(mode, 0, numVertices);
		else glDrawElements(mode, numIndices, GL_UNSIGNED_INT, nullptr);
	}

	void Model::draw(GLenum mode, GLint first, GLsizei count) const
	{
		if(EBO == nullptr) glDrawArrays(mode, first, count);
		else glDrawElements(mode, count, GL_UNSIGNED_INT, nullptr);
	}

	void Model::set_vbo(VertexBuffer *vertexBuffer, size_t numVertices, const VertexDescriptor &layout)
	{
		VBO = vertexBuffer;
		this->numVertices = numVertices;

		VBO->bind();

		for(auto &optAttribute : layout.attributes)
		{
			if(!optAttribute.has_value()) continue;

			auto &attribute = optAttribute.value();
			set_vertex_attribute(attribute.index, attribute.size, attribute.type, layout.stride, attribute.offset, attribute.normalized);
		}

		VBO->unbind();
	}

	void Model::set_ebo(IndexBuffer *indexBuffer, size_t numIndices)
	{
		EBO = indexBuffer;
		this->numIndices = numIndices;

		EBO->bind();
	}

	GLuint Model::get_vao() const
	{
		return VAO;
	}

	const VertexBuffer &Model::get_vbo() const
	{
		return *VBO;
	}

	const IndexBuffer &Model::get_ebo() const
	{
		return *EBO;
	}
}
