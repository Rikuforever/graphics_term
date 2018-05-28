#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuseMap;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec2 TexCoord;

uniform Material material;

out vec4 frag_color;

void main()
{
	frag_color = vec4(vec3(texture(material.diffuseMap, TexCoord)) , 1.0f);
}
