#include "shapes.hpp"

namespace shape
{
	MeshData generate_unit_cone(const gl::VertexDescriptor &layout, const size_t circlePrecision, const size_t numLevels)
	{
		if(!layout.has_attribute("position")) throw std::invalid_argument("A position attribute is required to generate the cone");

		// Vertex generation
		const size_t components = layout.stride / sizeof(GLfloat);
		const size_t requiredVertices = circlePrecision * (numLevels + 1) * components;
		std::vector<GLfloat> vertices(requiredVertices);

		for(size_t level = 0; level <= numLevels; level++)
		{
			for(size_t i = 0; i < circlePrecision; i++)
			{
				const size_t vertexIndex = (level * circlePrecision + i) * components;

				GLfloat *const vertex = &vertices[vertexIndex];

				GLfloat *const vPosition = vertex + layout.get_attribute("position").offset/sizeof(GLfloat);

				float height = (float)level / numLevels;

				// As the height gets bigger, the radius gets smaller
				vPosition[0] = glm::cos(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height); // x
				vPosition[1] = glm::sin(i * M_PI * 2.f / (circlePrecision - 1) ) * (1.f - height); // y
				vPosition[2] = height; // z

				if(layout.has_attribute("normal"))
				{
					auto &attrNormal = layout.get_attribute("normal");
					GLfloat *const vNormal = vertex + attrNormal.offset/gl::get_sizeof_type(attrNormal.type);

					// Get vector orthogonal to generator
					glm::vec3 generator = glm::vec3(-vPosition[0], vPosition[1], 1.0f);
					glm::vec3 normal = glm::cross(generator, glm::cross(glm::vec3(0.f, 0.f, 1.f), generator));

					normal = glm::normalize(normal);

					vNormal[0] = normal.x;
					vNormal[1] = normal.y;
					vNormal[2] = normal.z;
				}

				if(layout.has_attribute("texCoord"))
				{
					size_t textureOffset = layout.get_attribute("texCoord").offset/sizeof(GLfloat);

					vertices[vertexIndex + textureOffset] = (float)i / circlePrecision;
					vertices[vertexIndex + textureOffset + 1] = height;
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
	}

	MeshData generate_disk(const gl::VertexDescriptor &layout, const glm::vec3 &normal, const float radius, const size_t circlePrecision)
	{
		if(!layout.has_attribute("position")) throw std::invalid_argument("A position attribute is required to generate a disk");

		size_t components = layout.stride / sizeof(GLfloat);
		size_t requiredVertices = (circlePrecision + 1) * components;

		std::vector<GLfloat> vertices(requiredVertices);

		size_t positionOffset = layout.get_attribute("position").offset / sizeof(GLfloat);
		vertices[positionOffset] = 0.f;
		vertices[positionOffset + 1] = 0.f;
		vertices[positionOffset + 2] = 0.f;

		for(size_t i = 0; i < circlePrecision; i++)
		{
			size_t currentVertex = (i + 1) * components;

			vertices[currentVertex + positionOffset] = glm::cos((float)i / circlePrecision * M_PI);
			vertices[currentVertex + positionOffset + 1] = 0.f;
			vertices[currentVertex + positionOffset + 2] = glm::sin((float)i / circlePrecision * M_PI);

			if(layout.has_attribute("normal"))
			{
				size_t normalOffset = layout.get_attribute("normal").offset / sizeof(GLfloat);

				*(glm::vec3 *)&vertices[currentVertex + normalOffset] = normal;
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
