#version 330 core

struct Material
{
	vec3 ambient;
	sampler2D diffuseMap;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;

uniform DirectionalLight dirLight;
uniform Material material;
uniform vec3 viewPos;

out vec4 frag_color;

void main()
{
	// Ambient
	vec3 ambient = dirLight.ambient * material.ambient * material.diffuse;
	
	// Diffuse
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(-dirLight.direction);
	float NdotL = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = dirLight.diffuse * NdotL * material.diffuse;

	// Specular - Blinn-Phong
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 halfDir = normalize(lightDir + viewDir);
	float NdotH = max(dot(normal, halfDir), 0.0);
	vec3 specular = dirLight.specular * material.specular * pow(NdotH, material.shininess);
	
	frag_color = vec4(ambient + diffuse, 1.0f);
}
