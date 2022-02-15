#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include <cstring>
#include <glm/glm.hpp>

#include <GL/glew.h>

namespace shape
{
	/// Generates a cone of radius and of height 1
	/// @param stride The stride, in bytes, of the given vertices
	/// @param positionOffset Offset, in bytes, of the position attribute
	/// @param normalOffset Offset, in bytes, to the normal attribute (default SIZE_MAX)
	/// @param textureOffset Offset, in bytes, to the texture coordinates (default SIZE_MAX)
	/// @param circlePrecision Number of vertices used to describe a cone's cross section (default 24)
	/// @param numLevels Number of cone cross sections (default 16)
	void generate_unit_cone(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const size_t stride, const size_t positionOffset, const size_t normalOffset = SIZE_MAX, const size_t textureOffset = SIZE_MAX, const size_t circlePrecision = 24, const size_t numLevels = 16);
}
