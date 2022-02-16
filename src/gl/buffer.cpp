#include "wrap/gl/buffer.hpp"

namespace gl
{
	template <BufferTarget Target>
	thread_local GLuint Buffer<Target>::bound = 0;

	template <BufferTarget Target>
	Buffer<Target>::Buffer()
	{
		glGenBuffers(1, &id);
	}

	template <BufferTarget Target>
	Buffer<Target>::Buffer(GLuint id, GLsizei size)
	{
		this->id = id;
		this->size = size;
	}

	template <BufferTarget Target>
	Buffer<Target>::Buffer(Buffer &&other)
	{
		this->id = other.id;
		other.id = 0;

		this->size = other.size;
		other.size = 0;
	}

	template <BufferTarget Target>
	Buffer<Target> &Buffer<Target>::operator=(Buffer &&other)
	{
		if(&other != this)
		{
			free(); // Free currently taken up space

			this->id = other.id;
			other.id = 0;

			this->size = other.size;
			other.size = 0;
		}

		return *this;
	}

	template <BufferTarget Target>
	Buffer<Target>::~Buffer()
	{
		free();
	}

	template <BufferTarget Target>
	void Buffer<Target>::set_data(const void *data, GLsizei size, GLenum usage)
	{
		GLuint current = get_bound();

		bind();

		glBufferData(Target, size, data, usage);
		this->size = size;

		bind(current);
	}

	template <BufferTarget Target>
	void Buffer<Target>::bind()
	{
		glBindBuffer(Target, id);

		bound = id;
	}

	template <BufferTarget Target>
	/* static */ void Buffer<Target>::bind(GLuint id)
	{
		glBindBuffer(Target, id);

		bound = id;
	}

	template <BufferTarget Target>
	/* static */ void Buffer<Target>::unbind()
	{
		glBindBuffer(Target, 0);

		bound = 0;
	}

	template <BufferTarget Target>
	GLuint Buffer<Target>::get_id() const
	{
		return id;
	}

	template <BufferTarget Target>
	GLsizei Buffer<Target>::get_size() const
	{
		return size;
	}

	template <BufferTarget Target>
	/* static */ GLuint Buffer<Target>::get_bound()
	{
		return Buffer<Target>::bound;
	}

	template <BufferTarget Target>
	void Buffer<Target>::free()
	{
		glDeleteBuffers(1, &id);

		id = 0;
		size = 0;
	}
}
