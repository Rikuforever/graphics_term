#include "Light.h"

Light::Light()
	: ambient(0.2f, 0.2f, 0.2f),
	diffuse(1.0f, 1.0f, 1.0f),
	specular(1.0f,1.0f,1.0f)
{
}

void Light::setUniform(ShaderProgram& shader)
{
	shader.setUniform("light.ambient", ambient);
	shader.setUniform("light.diffuse", diffuse);
	shader.setUniform("light.specular", specular);
}

DirLight::DirLight()
	:direction(0.0f, -0.9f, -0.17f)
{
}

void DirLight::setUniform(ShaderProgram& shader)
{
	shader.setUniform("dirLight.direction", direction);
	shader.setUniform("dirLight.ambient", ambient);
	shader.setUniform("dirLight.diffuse", diffuse);
	shader.setUniform("dirLight.specular", specular);
}
