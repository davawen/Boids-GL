#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec4 Position;
out vec3 Normal;
out vec2 TexCoord;


void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	Position = gl_Position;
	Normal = mat3(uModel) * aNormal;
	TexCoord = aTexCoord;
}
