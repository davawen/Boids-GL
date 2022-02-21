#version 460 core

out vec4 FragColor;

uniform vec3 uObjectColor;
uniform vec3 uLightColor;
uniform vec3 uLightPos;

in vec3 FragPos;
in vec3 Normal;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambientColor = vec3(0.2, 0.3, 0.3);
	vec3 ambient = ambientStrength * uLightColor + ambientStrength * ambientColor;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(uLightPos - FragPos);

	float diffuseStrength = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseStrength * uLightColor;

	FragColor = vec4((ambient + diffuse) * uObjectColor, 1.0);
}
