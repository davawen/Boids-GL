#pragma once

#include <array>
#include <optional>
#include <tuple>
#include <stdexcept>

#include <GL/glew.h>

#ifndef VERTEX_LAYOUT_SIZE
	#define VERTEX_LAYOUT_SIZE 16
#endif

namespace gl
{
	struct Layout
	{
		struct Attribute
		{
			GLuint index; // Used in shader with (location = xxx)
			GLint size; // Number of components (1, 2, 3 or 4)
			GLenum type; // Type (GL_INT, GL_FLOAT, GL_BYTE, etc...)
			size_t offset; // Offset in bytes from the start of vertex attributes
			GLboolean normalized = GL_FALSE; // See documentation of glVertexAttribPointer
		};

		GLsizei stride; // Byte offset between consecutive generic vertex attributes

		std::array<std::optional<Attribute>, VERTEX_LAYOUT_SIZE> attributes;

		Layout();
		Layout(GLsizei stride, std::initializer_list<Attribute> init)
		{
			attributes.fill(std::nullopt);

			for(auto it = init.begin(); it != init.end(); it++)
			{
				attributes[it->index] = *it;
			}

			this->stride = stride;
		}

		/// Sets the given attribute according to the inputs index, overwriting any previous one before it
		inline void set_attribute(const Attribute &attribute)
		{
			if(attribute.index >= VERTEX_LAYOUT_SIZE) throw std::out_of_range("Attribute index greater than VertexLayout array size");

			attributes[attribute.index] = attribute;
		}

		inline std::optional<Attribute> remove_attribute(const GLuint index)
		{
			auto attribute = attributes[index];

			attributes[index] = std::nullopt;

			return attribute;
		}
	};
}
