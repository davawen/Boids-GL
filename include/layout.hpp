#pragma once

#include <vector>
#include <unordered_map>
#include <tuple>
#include <stdexcept>
#include <optional>
#include <fmt/core.h>

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
			GLsizei offset; // Offset in bytes from the start of the vertex
			GLboolean normalized = GL_FALSE; // See documentation of glVertexAttribPointer

			/// @returns The size of the attribute's type times its number of components
			inline size_t get_size() const
			{
				return size*gl::get_sizeof_type(type);
			}

			/// Sets the value of this attribute in a given vertex
			/// @tparam T Struct type of the vertex
			/// @tparam J Type of the value, size must be equal to the attributes size
			template <typename VertexType, typename ValueType>
			inline void set_vertex_value(VertexType &vertex, const ValueType &value) const
			{
				// Avoid overridding any data
				if(sizeof(ValueType) > get_size())
					throw std::invalid_argument(fmt::format("Value given to set_vertex_value differs in size to gl::VertexDescriptor::Attribute: {} bytes vs {} bytes.", sizeof(ValueType), get_size()));

				// memcpy(static_cast<void *>(static_cast<char *>(&vertex) + offset), static_cast<void *>(&value), get_size());

				// Advances from the start of the vertice's address to the attribute's offset
				// TODO: Find a more type-safe way of doing this
				*(ValueType *)((char *)(&vertex) + offset) = value;
			}
		};

		GLsizei stride; // Byte offset between consecutive generic vertex attributes

		std::vector<Attribute> attributes;

		/// Used to expose attributes with special meanings, such as positions, texture coordinates, normals, etc...
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

		inline void append_attribute(const std::string &name, const Attribute &attribute)
		{
			attributes.push_back(attribute);
			
			namedAttributes[name] = attributes.size() - 1;

			this->stride += attribute.get_size();
		}

		inline void set_attribute(const GLuint index, const Attribute &attribute)
		{
			attributes[index] = attribute;
		}

		inline void set_attribute(const GLuint index, const std::string &name, const Attribute &attribute)
		{
			attributes[index] = attribute;

			namedAttributes[name] = index;
		}

		inline bool has_attribute(const std::string &name) const
		{
			return namedAttributes.find(name) != namedAttributes.end();
		}

		inline const Attribute &get_attribute(const std::string &name) const
		{
			return attributes[namedAttributes.at(name)];
		}

		inline void reset_attributes()
		{
			stride = 0;
			attributes.clear();
			namedAttributes.clear();
		}
	};
}
