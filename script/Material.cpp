#include "Material.h"

#define TEX_UNIT 0

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
	shader.setUniform("material.diffuse", diffuse);
	shader.setUniform("material.specular", specular);
	shader.setUniform("material.shininess", shininess);

	if(mTexture2DPtr != nullptr)
		shader.setUniform("material.diffuseMap", TEX_UNIT); // or setUniformMap
}

void Material::bindTexture(Texture2D& texture)
{
	mTexture2DPtr = &texture;
}

void Material::bind()
{
	if (mTexture2DPtr != nullptr)
		mTexture2DPtr->bind(TEX_UNIT);
}
void Material::unbind()
{
	if (mTexture2DPtr != nullptr)
		mTexture2DPtr->unbind(TEX_UNIT);
}

