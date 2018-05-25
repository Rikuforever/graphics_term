#ifndef LIGHT_H
#define LIGHT_H

#include "ShaderProgram.h"

#include "glm/glm.hpp"

class Light
{
public:
	Light();

	virtual void setUniform(ShaderProgram& shader);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};


class DirLight : public Light
{
public:
	DirLight();

	void setUniform(ShaderProgram& shader) override;

	glm::vec3 direction;
};

#endif