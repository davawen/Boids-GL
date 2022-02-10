#pragma once
#include <iostream>

#include <GL/glew.h>

#include "layout.hpp"

namespace gl
{
	class Model
	{
		private:
			GLuint VAO, VBO;
			GLuint EBO; // A value of 0 for EBO means that indices are not used

			size_t numVertices, numIndices;

			void free();

			/// Sets vertex attributes of the VBO
			/// WARNING: Model must be bound when using this function
			/// WARNING: VBO must be bound when using this function
			/// @param layout The index of the generic vertex attribute to be modified 
			/// @param size The number of components per generic vertex attribute. Must be 1, 2, 3, or 4.
			/// @param type The data type of each component. Can be GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT
			/// @param stride Byte offset between consecutive vertex attributes. If stride is 0, it is implicit that vertex attributes are tightly packed (ie: only one vertex attribute)
			/// @param offset The byte offset of the attribute from the start of a vertex in the data array.
			/// @param normalized Wether fixed-point data values should be normalized or converted directly as fixed_point values. False by default.
			void set_vertex_attribute(GLuint layout, GLint size, GLenum type, GLsizei stride, size_t offset, GLboolean normalized = GL_FALSE);

		public:
			/// Creates a Vertex Buffer and a Vertex Array associated with the Model.
			/// NOTE: All buffers will be unbounded after the constructor.
			/// @param sizeOfVertex The number of individual elements within a single vertex. For vertices storing xyz positions and uv texture coordinates, that would be 5.
			/// @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
			Model(GLfloat *vertices, size_t numVertices, size_t sizeOfVertex, GLenum usage, const Layout &layout);	

			/// Creates a Vertex Buffer, an Index Buffer and a Vertex Array associated with the Model.
			/// NOTE: All buffers will be unbounded after the constructor.
			/// @param sizeOfVertex The number of individual elements within a single vertex. For vertices storing xyz positions and uv texture coordinates, that would be 5.
			/// @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
			Model(GLfloat *vertices, size_t numVertices, size_t sizeOfVertex, GLint *indices, size_t numIndices, GLenum usage, const Layout &layout);

			Model(const Model &) = delete;
			Model &operator=(const Model &) = delete;

			Model(Model &&other);
			Model &operator=(Model &&other);

			~Model();

			void bind();
			static void unbind();

			/// Draws the whole model
			/// WARNING: Model must be bound before drawing
			/// @param mode The kind of primitives to render. Can be GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY or GL_PATCHES
			void draw(GLenum mode) const;

			/// Draws a part of the vertex array
			/// WARNING: Model must be bound before drawing
			/// @param mode The kind of primitives to render. Can be GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY or GL_PATCHES
			/// @param first The starting vertex from which to start drawing (unused with indices)
			/// @param count Number of vertices/indices to draw
			void draw(GLenum mode, GLint first, GLsizei count) const;

			GLuint get_vao() const;
			GLuint get_vbo() const;
			GLuint get_ebo() const;
	};
}
