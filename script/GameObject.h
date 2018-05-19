#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "ShaderProgram.h"
#include "Texture2D.h"

class GameObject
{
public :
	GameObject();
	~GameObject();

	glm::vec3 position;
	glm::vec3 rotation;	// degree

	// GLUT callbacks
	void load();
	void draw();

	void bindWindow(int& width, int& height);
	void bindShader(ShaderProgram& shader);
	void bindTexture(Texture2D& texture);
private:
	GLuint mVAO;
	ShaderProgram* mShaderPtr;
	Texture2D* mTexturePtr;

	int* wWidthPtr;
	int* wHeightPtr;
};

#endif

