#version 460 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 TexCoord;
out vec4 Position;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
	Position = gl_Position;
	TexCoord = aTexCoord;
}
