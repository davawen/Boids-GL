#version 460 core

out vec4 FragColor;

in vec4 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	vec3 norm = normalize(Normal); // May not be normalized after interpolation

	FragColor = mix( texture(Texture1, TexCoord), texture(Texture2, TexCoord), 0.3 );

	// FragColor = vec4( norm * 0.5 + 0.5, 1.0 );
}
