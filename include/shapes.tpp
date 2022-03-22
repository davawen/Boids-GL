#pragma once

#include "shapes.hpp"

namespace shape
{
	template <typename T>
	MeshData<T> generate_unit_cone(const gl::VertexDescriptor &layout, const size_t circlePrecision, const size_t numLevels)
	{
		if(!layout.has_attribute("position")) throw std::invalid_argument("A position attribute is required to generate a cone.");

		// Vertex generation
		const size_t requiredVertices = circlePrecision * (numLevels + 1);
		std::vector<T> vertices(requiredVertices);

		for(size_t level = 0; level <= numLevels; level++)
		{
			for(size_t i = 0; i < circlePrecision; i++)
			{
				const size_t vertexIndex = (level * circlePrecision + i);

				T &vertex = vertices[vertexIndex];

				// As the height gets bigger, the radius gets smaller
				float height = (float)level / numLevels;

				glm::vec3 position(
					glm::cos(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height), // x
					glm::sin(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height), // y
					height // z
				);

				layout.get_attribute("position").set_vertex_value(vertex, position);

				if(layout.has_attribute("normal"))
				{
					// Get vector orthogonal to generator
					glm::vec3 generator = glm::vec3(-position.x, position.y, 1.0f);
					glm::vec3 normal = glm::cross(generator, glm::cross(glm::vec3(0.f, 0.f, 1.f), generator));

					normal = glm::normalize(normal);

					layout.get_attribute("normal").set_vertex_value(vertex, normal);
				}

				if(layout.has_attribute("texCoord"))
				{
					glm::vec2 texCoord( (float)i / circlePrecision, height);

					layout.get_attribute("texCoord").set_vertex_value(vertex, texCoord);
				}
			}
		}

		// Indice generation
		// 6 indice per square * number of "squares"
		const size_t requiredIndices = 6*(circlePrecision - 1)*(numLevels);
		
		std::vector<GLuint> indices(requiredIndices);

		size_t indexNum = 0;

		for(size_t level = 0; level < numLevels; level++)
		{
			for(size_t i = 0; i < circlePrecision - 1; i++)
			{
				const size_t levelIndex = level * circlePrecision;

				// o 
				// | ╲ 
				// o--o
				indices[indexNum++] = levelIndex + i;
				indices[indexNum++] = levelIndex + i + 1; // one to the right
				indices[indexNum++] = levelIndex + circlePrecision + i; // go one level up

				// o--o
				//  ╲ |
				//	o
				indices[indexNum++] = levelIndex + circlePrecision + i; // go one level up
				indices[indexNum++] = levelIndex + circlePrecision + i + 1; // one level up and to the right
				indices[indexNum++] = levelIndex + i + 1; // one to the right
			}
		}

		return { vertices, indices };
	};

	template <typename T>
	MeshData<T> generate_disk(const gl::VertexDescriptor &layout, const glm::vec3 &position, const glm::vec3 &normal, const float radius, const size_t circlePrecision)
	{
		if(!layout.has_attribute("position")) throw std::invalid_argument("A position attribute is required to generate a disk");

		size_t requiredVertices = (circlePrecision + 1);

		std::vector<T> vertices(requiredVertices);

		auto &positionAttribute = layout.get_attribute("position");
		positionAttribute.set_vertex_value(vertices[0], position);

		for(size_t i = 0; i < circlePrecision; i++)
		{
			T &currentVertex = vertices[i + 1];

			positionAttribute.set_vertex_value(currentVertex, glm::vec3(
				glm::cos((float)i / circlePrecision * M_PI) * radius,
				0.f,
				glm::sin((float)i / circlePrecision * M_PI) * radius
			));

			if(layout.has_attribute("normal"))
			{
				layout.get_attribute("normal").set_vertex_value(currentVertex, normal);
			}
		}
		
		const size_t requiredIndices = circlePrecision * 3;
		std::vector<GLuint> indices(requiredIndices);

		size_t idx = 0;
		for(size_t i = 0; i < circlePrecision; i++)
		{
			indices[idx++] = 0;
			indices[idx++] = i + 0;
			indices[idx++] = (i + 1) % circlePrecision + 1;
		}

		return { vertices, indices };
	}
}
