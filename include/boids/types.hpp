#pragma once

#include <glm/glm.hpp>
#include <layout.hpp>

namespace boids
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	gl::VertexDescriptor create_vertex_descriptor();
}
