#include "Material.h"

Material::Material()
	:ambient(0.1f,0.1f,0.1f),
	diffuse(1.0f,1.0f,1.0f),
	diffuseMap(0),
	specular(0.8f,0.8f,0.8f),
	shininess(32.0f)
{
}

void Material::setUniform(ShaderProgram& shader)
{	
	shader.setUniform("material.ambient", ambient);
	shader.setUniform("material.diffuseMap", 0);
	shader.setUniform("material.diffuse", diffuse);
	shader.setUniform("material.specular", specular);
	shader.setUniform("material.shininess", shininess);
}
