#pragma once
#include <string>
#include <stdexcept>

#include <stb_image.h>

namespace stb
{
	struct Image
	{
		int width, height, nrChannels;
		uint8_t *data;

		Image();
		Image(const std::string &filename);

		/// Disallow copy constructor
		Image(const Image &other) = delete;
		Image &operator =(const Image &other) = delete;

		Image(Image &&other);
		Image &operator=(Image &&other);

		~Image();

		/// Loads a new image and deletes any previously loaded image
		void load(const std::string &filename);
	};
}
