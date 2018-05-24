#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "ShaderProgram.h"
#include "Texture2D.h"

class Engine;

class GameObject
{
public :
	GameObject();
	~GameObject();

	glm::vec3 position;
	glm::vec3 rotation;	// degree
	glm::vec3 scale;

	// GLUT callbacks
	virtual void load();
	virtual void draw();

	void bindEngine(Engine* enginePtr);
	void bindShader(ShaderProgram& shader);
	void bindTexture(Texture2D& texture);
protected:
	GLuint mVAO;
	ShaderProgram* mShaderPtr;
	Texture2D* mTexturePtr;

	Engine* mEnginePtr;
};

#endif

