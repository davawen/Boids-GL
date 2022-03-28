#include "boids/types.hpp"


namespace boids
{
	gl::VertexDescriptor create_vertex_descriptor()
	{
		gl::VertexDescriptor layout;

		layout.append_attribute("position", { .index = 0, .size = 3, .type = GL_FLOAT, .offset = offsetof(Vertex, position) }); // Positions (x, y, z)
		layout.append_attribute("normal", { .index = 1, .size = 3, .type = GL_FLOAT, .offset = offsetof(Vertex, normal) }); // Normals (x, y, z)
		layout.append_attribute("texCoord", { .index = 2, .size = 2, .type = GL_FLOAT, .offset = offsetof(Vertex, texCoord) });  // Textures (u, v)

		return layout;
	}
}
