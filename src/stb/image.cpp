#include "wrap/stb/image.hpp"

namespace stb
{
	Image::Image()
	{
		width = 0;
		height = 0;
		nrChannels = 0;

		data = nullptr;
	}

	Image::Image(const std::string &filename)
	{
		data = nullptr;

		load(filename);
	}

	Image::Image(Image &&other)
	{
		width = other.width;
		height = other.height;
		nrChannels = other.nrChannels;
		data = other.data;

		other.data = nullptr;
	}

	Image &Image::operator=(Image &&other)
	{
		if(&other != this)
		{
			if(data != nullptr) stbi_image_free(data);

			width = other.width;
			height = other.height;
			nrChannels = other.nrChannels;
			data = other.data;

			other.data = nullptr;
		}

		return *this;
	}

	Image::~Image()
	{
		if(data != nullptr) stbi_image_free(data);

		data = nullptr;
	}

	void Image::load(const std::string &filename)
	{
		if(data != nullptr) stbi_image_free(data);

		data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

		if(!data) throw std::runtime_error("Failed to load image " + filename);
	}
}
