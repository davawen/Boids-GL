#pragma once

#include <vector>
#include <unordered_map>
#include <tuple>
#include <stdexcept>

#include <GL/gl.h>

// Number of attributes to preemptively reserve
#ifndef VERTEX_DESCRIPTOR_ALLOC
	#define VERTEX_DESCRIPTOR_ALLOC 3
#endif

namespace gl
{
	size_t get_sizeof_type(GLenum type);

	struct VertexDescriptor
	{
		struct Attribute
		{
			GLuint index; // Used in shader with (location = xxx)
			GLint size; // Number of components (1, 2, 3 or 4)
			GLenum type; // Type (GL_INT, GL_FLOAT, GL_BYTE, etc...)
			GLsizei offset; // Offset in bytes from the start of the vector
			GLboolean normalized = GL_FALSE; // See documentation of glVertexAttribPointer
		};

		GLsizei stride; // Byte offset between consecutive generic vertex attributes

		std::vector<Attribute> attributes;

		std::unordered_map<std::string, size_t> namedAttributes;


		VertexDescriptor()
		{
			stride = 0;
			attributes.reserve(VERTEX_DESCRIPTOR_ALLOC);
		}

		VertexDescriptor(std::initializer_list<Attribute> init)
		{
			stride = 0;
			attributes.reserve(init.size());

			for(auto it = init.begin(); it != init.end(); it++)
			{
				append_attribute(*it);
			}
		}

		inline Attribute &operator[](const GLuint index)
		{
			return attributes[index];
		}

		inline const Attribute &operator[](const GLuint index) const
		{
			return attributes[index];
		}

		inline void append_attribute(const Attribute &attribute)
		{
			attributes.push_back(attribute);
			this->stride += get_sizeof_type(attribute.type);
		}

		inline void append_attribute(std::string name, const Attribute &attribute)
		{
			attributes.push_back(attribute);
			this->stride += get_sizeof_type(attribute.type);
		}

		inline void set_attribute(const GLuint index, const Attribute &attribute)
		{
			attributes[index] = attribute;
		}

		inline void reset_attributes()
		{
			stride = 0;
			attributes.clear();
		}
	};
}
