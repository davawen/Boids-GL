#include "shapes.hpp"

namespace shape
{
	MeshData generate_unit_cone(const size_t stride, const size_t positionOffset, const size_t normalOffset, const size_t circlePrecision, const size_t numLevels)
	{
		// Vertex generation
		const size_t components = stride / sizeof(GLfloat);
		const size_t requiredVertices = circlePrecision * (numLevels + 1) * components;
		std::vector<GLfloat> vertices(requiredVertices);

		for(size_t level = 0; level <= numLevels; level++)
		{
			for(size_t i = 0; i < circlePrecision; i++)
			{
				const size_t vertexIndex = (level * circlePrecision + i) * components;

				GLfloat *const vertex = &vertices[vertexIndex];
				GLfloat *const vPosition = vertex + positionOffset/sizeof(GLfloat);

				float height = (float)level / numLevels;

				// As the height gets bigger, the radius gets smaller
				vPosition[0] = glm::cos(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height); // x
				vPosition[1] = glm::sin(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height); // y
				vPosition[2] = height; // z

				if(normalOffset != SIZE_MAX)
				{
					GLfloat *const vNormal = vertex + normalOffset/sizeof(GLfloat);

					// Get vector orthogonal to generator
					glm::vec3 generator = glm::vec3(-vPosition[0], vPosition[1], 1.0f);
					glm::vec3 normal = glm::cross(generator, glm::cross(glm::vec3(0.f, 0.f, 1.f), generator));

					normal = glm::normalize(normal);

					vNormal[0] = normal.x;
					vNormal[1] = normal.y;
					vNormal[2] = normal.z;
				}

				// if(textureOffset != SIZE_MAX)
				// {
				// 	vertices[vertexIndex + textureOffset/sizeof(GLfloat)] = (float)i / circlePrecision;
				// 	vertices[vertexIndex + textureOffset/sizeof(GLfloat) + 1] = height;
				// }
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
	}
}
