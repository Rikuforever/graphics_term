#include "GameMap.h"
#include "Engine.h"

#include "glm/gtc/matrix_transform.hpp"

#define BASE 100

GameMap::GameMap()
	:GameObject()
{
}


GameMap::~GameMap()
{
}

void GameMap::load()
{
	std::vector<glm::vec3> posList;

	// convert map data into vec3 list
	for (std::map<int, int>::iterator idata = mData.begin(); idata != mData.end(); idata++)
	{
		if(idata->second == 1)
		{
			posList.push_back(getPosition(idata->first));
		}
	}

	// create vertices
	for(int posIdx = 0; posIdx < posList.size(); posIdx++)
	{
		for (int verIdx = 0; verIdx < VERTICES_LENGTH; verIdx += 3) {
			glm::vec3 vertex;
			vertex.x = cubeVertices[verIdx] * 0.5 + posList[posIdx].x;
			vertex.y = cubeVertices[verIdx + 1] * 0.5 + posList[posIdx].y;
			vertex.z = cubeVertices[verIdx + 2] * 0.5 + posList[posIdx].z;
			mVertices.push_back(vertex);
		}
	}

	// Create & Bind buffer
	GLuint vbo;
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &vbo);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(glm::vec3), &mVertices[0], GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// Unbind buffer
	glBindVertexArray(0);
}

void GameMap::draw()
{
	// Ignore texture
	// Bind shader
	if (mShaderPtr != nullptr) {
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
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindVertexArray(0);
}

int GameMap::getData(int x, int y, int z) 
{
	if (mData.find(key(x, y, z)) == mData.end())
		return -1;	// empty
	else
		return mData[key(x, y, z)];
}

void GameMap::setData(int x, int y, int z, int value)
{
	mData[key(x, y, z)] = value;
}

int GameMap::key(int x, int y, int z) {
	return x + BASE * y + pow(BASE, 2) * z;
}

glm::vec3 GameMap::getPosition(int x, int y, int z)
{
	glm::vec3 result;

	result.z = (float)z + mDefaultPos.z;
	result.y = (float)y + mDefaultPos.y;
	result.x = (float)x + mDefaultPos.x;

	return result;
}

glm::vec3 GameMap::getPosition(int keyValue)
{
	glm::vec3 result;

	result.z = (float)keyValue / pow(BASE, 2) + mDefaultPos.z;
	result.y = ((float)keyValue - key(0, 0, result.z)) / BASE + mDefaultPos.y;
	result.x = ((float)keyValue - key(0, result.y, result.z)) + mDefaultPos.x;

	return result;
}

