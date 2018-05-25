#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShaderProgram.h"

#include "glm/glm.hpp"

class Material
{
public:
	Material();

	void setUniform(ShaderProgram& shader);

	glm::vec3 ambient;
	glm::vec3 diffuse;
	GLuint diffuseMap;	// texUnit (for Texture2D)
	glm::vec3 specular;
	float shininess;
};

#endif