#pragma once

#include <unordered_map>

#include <GL/glew.h>

namespace gl
{
	enum BufferTarget
	{
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ATOMIC_COUNTER_BUFFER = GL_ATOMIC_COUNTER_BUFFER,
		COPY_READ_BUFFER = GL_COPY_READ_BUFFER,
		COPY_WRITE_BUFFER = GL_COPY_WRITE_BUFFER,
		DISPATCH_INDIRECT_BUFFER = GL_DISPATCH_INDIRECT_BUFFER,
		DRAW_INDIRECT_BUFFER = GL_DRAW_INDIRECT_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
		PIXEL_PACK_BUFFER = GL_PIXEL_PACK_BUFFER,
		PIXEL_UNPACK_BUFFER = GL_PIXEL_UNPACK_BUFFER,
		QUERY_BUFFER = GL_QUERY_BUFFER,
		SHADER_STORAGE_BUFFER = GL_SHADER_STORAGE_BUFFER,
		TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
		TRANSFORM_FEEDBACK_BUFFER = GL_TRANSFORM_FEEDBACK_BUFFER,
		UNIFORM_BUFFER = GL_UNIFORM_BUFFER,
	};

	template <BufferTarget Target>
	class Buffer
	{
	public:
		Buffer();

		/// Creates a buffer from an already constructed one
		Buffer(GLuint id, GLsizei size);

		Buffer(Buffer &) = delete;
		Buffer &operator=(Buffer &) = delete;

		Buffer(Buffer &&other);
		Buffer &operator=(Buffer &&other);

		~Buffer();

		/// Sets the internal data of the buffer.
		/// @param data Array of data, or nullptr if no data is to be set.
		/// @param size The size of the array in bytes
		/// @param usage Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY. 
		void set_data(const void *data, GLsizei size, GLenum usage);

		void bind();

		static void bind(GLuint id);
		static void unbind();

		GLuint get_id() const;
		GLsizei get_size() const;
		static GLuint get_bound();

	private:
		void free();

		GLuint id;
		GLsizei size;
		
		static thread_local GLuint bound;
	};

	template class Buffer<BufferTarget::ARRAY_BUFFER>;
	template class Buffer<BufferTarget::ATOMIC_COUNTER_BUFFER>;
	template class Buffer<BufferTarget::COPY_READ_BUFFER>;
	template class Buffer<BufferTarget::COPY_WRITE_BUFFER>;
	template class Buffer<BufferTarget::DISPATCH_INDIRECT_BUFFER>;
	template class Buffer<BufferTarget::DRAW_INDIRECT_BUFFER>;
	template class Buffer<BufferTarget::ELEMENT_ARRAY_BUFFER>;
	template class Buffer<BufferTarget::PIXEL_PACK_BUFFER>;
	template class Buffer<BufferTarget::PIXEL_UNPACK_BUFFER>;
	template class Buffer<BufferTarget::QUERY_BUFFER>;
	template class Buffer<BufferTarget::SHADER_STORAGE_BUFFER>;
	template class Buffer<BufferTarget::TEXTURE_BUFFER>;
	template class Buffer<BufferTarget::TRANSFORM_FEEDBACK_BUFFER>;
	template class Buffer<BufferTarget::UNIFORM_BUFFER>;	

	using VertexBuffer = Buffer<BufferTarget::ARRAY_BUFFER>;
	using IndexBuffer = Buffer<BufferTarget::ELEMENT_ARRAY_BUFFER>;
}
