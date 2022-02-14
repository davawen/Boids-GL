#pragma once

#include <vector>
#include <functional>
#include <cstring>
#include <glm/glm.hpp>

#include <GL/glew.h>

namespace shape
{
	/// Generates a cone of radius and of height 1
	/// @param stride The stride, in bytes, of the given vertices
	/// @param offset Offset, in bytes, of the position attribute
	/// @param vertexCallback Function called for each vertex set.
	/// @signature `void vertexCallback(GLfloat *vertex, size_t index, size_t level, const size_t circlePrecision, const size_t numLevels)`
	/// @param circlePrecision Number of vertices used to describe a cone's cross section
	/// @param numLevels Number of cone cross sections
	void generate_unit_cone_positions(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const size_t stride, const size_t offset, void (*vertexCallback)(GLfloat *, size_t, size_t, const size_t, const size_t) = nullptr, const size_t circlePrecision = 24, const size_t numLevels = 16);
}
