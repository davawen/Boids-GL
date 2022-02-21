#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uNormal;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 FragPos;
out vec3 Normal;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	FragPos = (uModel * vec4(aPos, 1.0f)).xyz;

	Normal = mat3(uNormal) * aNormal;
}
