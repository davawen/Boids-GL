#include "shapes.hpp"
#include <cmath>

namespace shape
{
	void generate_unit_cone_positions(std::vector<GLfloat> &vertices, std::vector<GLuint> &indices, const size_t stride, const size_t offset, void (*vertexCallback)(GLfloat *, size_t, size_t, const size_t, const size_t), const size_t circlePrecision, const size_t numLevels)
	{
		// Vertex generation
		const size_t components = stride / sizeof(GLfloat);
		const size_t requiredVertices = circlePrecision * (numLevels + 1) * components;
		if(vertices.size() < requiredVertices) vertices.resize(requiredVertices);

		for(size_t level = 0; level <= numLevels; level++)
		{
			for(size_t i = 0; i < circlePrecision; i++)
			{
				const size_t vertexIndex = (level * circlePrecision + i) * components;
				const size_t vertexPositionIndex = vertexIndex + offset/sizeof(GLfloat);

				float height = (float)level / numLevels;

				// As the height gets bigger, the radius gets smaller
				vertices[vertexPositionIndex] = glm::cos(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height); // x
				vertices[vertexPositionIndex + 1] = glm::sin(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height); // y
				vertices[vertexPositionIndex + 2] = height; // z

				if(vertexCallback != nullptr)
				{
					vertexCallback(&vertices[vertexIndex], i, level, circlePrecision, numLevels);
				}
			}
		}

		// Indice generation
		// 6 indice per square * number of "squares"
		const size_t requiredIndices = 6*(circlePrecision - 1)*(numLevels);
		if(indices.size() < requiredIndices) indices.resize(requiredIndices);

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
	}
}
