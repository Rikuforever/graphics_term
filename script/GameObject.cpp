#include "GameObject.h"
#include "Engine.h"

#include "glm/gtc/matrix_transform.hpp"

GameObject::GameObject()
	: position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f)
{
}

GameObject::~GameObject()
{
}

void GameObject::load()
{
	#pragma region TEMP DATA
	GLfloat vertices[] = {
		// position		 // tex coords

		// front face
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		// back face
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		// left face
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

		// right face
		1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

		// top face
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

		// bottom face
		-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	};
#pragma endregion 

	// Create & Bind buffer
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);
	// Texture Coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind buffer
	glBindVertexArray(0);
}

void GameObject::draw()
{
	// Bind texture
	if (mTexturePtr != nullptr)
		mTexturePtr->bind(0);

	// Bind shader
	if(mShaderPtr != nullptr)
	{
		// Compute matrix
		glm::mat4 model, view, projection;
		model = glm::translate(model, position) *
			glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
			glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)) *
			glm::scale(model, scale);
		view = mEnginePtr->getCamera().getViewMatrix();
		projection = glm::perspective(glm::radians(45.0f), (float)(mEnginePtr->gWindowWidth) / (float)(mEnginePtr->gWindowHeight), 0.1f, 100.0f);


		mShaderPtr->bind();
		mShaderPtr->setUniform("model", model);
		mShaderPtr->setUniform("view", view);
		mShaderPtr->setUniform("projection", projection);
	}

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	// Unbind texture
	if (mTexturePtr != nullptr)
		mTexturePtr->unbind(0);

	// Unbind shader
	if (mShaderPtr != nullptr)
		mShaderPtr->unbind();
}

void GameObject::bindEngine(Engine* enginePtr)
{
	mEnginePtr = enginePtr;
}

void GameObject::bindShader(ShaderProgram & shader) {
	mShaderPtr = &shader;
}

void GameObject::bindTexture(Texture2D & texture)
{
	mTexturePtr = &texture;
}

