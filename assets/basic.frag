#version 460 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 Position;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	FragColor = mix( texture(Texture1, TexCoord), texture(Texture2, TexCoord), 0.3 );
	//FragColor = vec4( Color, 1.0f );
}
