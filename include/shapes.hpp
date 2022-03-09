#pragma once

#include <cstdint>
#include <vector>
#include <utility>
#include <functional>
#include <cstring>
#include <glm/glm.hpp>

#include <GL/glew.h>

#include "layout.hpp"

namespace shape
{
	using MeshData = std::pair<std::vector<GLfloat>, std::vector<GLuint>>;

	/**
	 * Generates a cone of radius and of height 1.
	 *
	 * @param layout Vertex layout of the output data
	 * @param circlePrecision Number of vertices used to describe a cone's cross section (default 24)
	 * @param numLevels Number of cone cross sections (default 16)
	*/
	MeshData generate_unit_cone(const gl::VertexDescriptor &layout, const size_t circlePrecision = 24, const size_t numLevels = 16);

	MeshData generate_disk(const gl::VertexDescriptor &layout, const glm::vec3 &normal = { 0.f, 1.f, 0.f }, const float radius = 1.f, const size_t circlePrecision = 24);

	MeshData generate_plane(const gl::VertexDescriptor &layout);

	/// @returns Only the vertices, no indices are given
	std::vector<GLfloat> generate_cube(const gl::VertexDescriptor &layout, float sideLength);

}
