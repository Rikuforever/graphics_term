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

	#pragma region MapData

		#pragma region mainmap
			setData(0, 0, 10, 1);
			setData(0, 1, 10, 1);
			setData(0, 2, 10, 1);
			setData(0, 3, 10, 1);
			setData(0, 3, 9, 1);
			setData(0, 3, 11, 1);
			setData(1, 0, 10, 1);
			setData(2, 0, 10, 1);
			setData(3, 0, 10, 1);
			setData(4, 0, 10, 1);
			setData(5, 0, 10, 1);
			setData(6, 0, 10, 1);
			setData(7, 1, 10, 1);
			setData(8, 2, 10, 1);
			setData(9, 3, 10, 1);
			setData(9, 4, 9, 1);
			setData(9, 5, 8, 1);
			setData(9, 6, 7, 1);
			setData(9, 6, 6, 1);
			setData(9, 6, 5, 1);
			setData(9, 6, 4, 1);
			setData(9, 6, 3, 1);
			setData(8, 7, 3, 1);
			setData(7, 8, 3, 1);
			setData(6, 9, 3, 1);
			setData(5, 10, 3, 1);
			setData(4, 10, 3, 1);
			setData(3, 10, 3, 1);
			setData(2, 10, 3, 1);
			setData(1, 10, 3, 1);
			setData(0, 10, 3, 1);
			setData(0, 9, 4, 1);
			setData(0, 8, 5, 1);
			setData(0, 7, 6, 1);
			setData(0, 6, 7, 1);
			setData(0, 6, 8, 1);
			setData(0, 6, 9, 1);
		#pragma endregion
		#pragma region root2
			setData(4, 1, 11, 1);
			setData(4, 2, 12, 1);
			setData(4, 3, 13, 1);
			setData(4, 4, 14, 1);
			setData(5, 3, 14, 1);
			setData(6, 2, 14, 1);
			setData(7, 1, 14, 1);
			setData(8, 1, 14, 1);
			setData(9, 1, 14, 1);
			setData(10, 1, 14, 1);
			setData(11, 1, 14, 1);
			setData(11, 1, 13, 1);
			setData(11, 1, 12, 1);
			setData(12, 1, 12, 1);
			setData(12, 1, 11, 1);
			setData(12, 1, 10, 1);
			setData(13, 1, 10, 1);
			setData(13, 1, 9, 1);
			setData(13, 1, 8, 1);
			setData(14, 1, 8, 1);
			setData(14, 1, 7, 1);
			setData(14, 1, 6, 1);
			setData(14, 2, 6, 1);
			setData(13, 3, 6, 1);
			setData(12, 4, 6, 1);
			setData(11, 5, 6, 1);
			setData(10, 6, 6, 1);
		#pragma endregion
		#pragma region trashmap
			setData(1, 1, 11, 1);
			setData(1, 1, 9, 1);
			setData(2, 1, 11, 1);
			setData(2, 1, 9, 1);
			setData(3, 1, 11, 1);
			setData(3, 1, 9, 1);
			setData(4, 0, 9, 1);
			setData(4, 1, 8, 1);
			setData(4, 2, 8, 1);
			setData(5, 1, 11, 1);
			setData(5, 1, 9, 1);
			setData(6, 1, 11, 1);
			setData(6, 1, 9, 1);
			setData(7, 2, 11, 1);
			setData(7, 2, 9, 1);
			setData(8, 3, 11, 1);
			setData(8, 3, 9, 1);
			setData(9, 7, 2, 1);
			setData(9, 8, 2, 1);
			setData(6, 10, 2, 1);
			setData(6, 11, 2, 1);
			setData(7, 9, 2, 1);
			setData(7, 10, 2, 1);
			setData(8, 8, 2, 1);
			setData(8, 9, 2, 1);
			setData(5, 11, 2, 1);
			setData(5, 12, 2, 1);
			setData(4, 11, 2, 1);
			setData(4, 12, 2, 1);
			setData(3, 11, 2, 1);
			setData(3, 12, 2, 1);
			setData(2, 11, 2, 1);
			setData(2, 12, 2, 1);
			setData(1, 11, 2, 1);
			setData(1, 12, 2, 1);
			setData(0, 11, 2, 1);
			setData(0, 12, 2, 1);
			setData(6, 12, 2, 1);
			setData(7, 11, 2, 1);
			setData(7, 12, 2, 1);
			setData(8, 12, 2, 1);
			setData(8, 11, 2, 1);
			setData(8, 10, 2, 1);
			setData(9, 12, 2, 1);
			setData(9, 11, 2, 1);
			setData(9, 10, 2, 1);
			setData(9, 9, 2, 1);
		#pragma endregion

		#pragma region secondMap
			setData(20, 20, 20, 1);
			setData(20, 20, 19, 1);
			setData(20, 20, 21, 1);
			setData(19, 20, 20, 1);
			setData(19, 20, 19, 1);
			setData(19, 20, 21, 1);
			setData(21, 20, 20, 1);
			setData(22, 20, 20, 1);
			setData(23, 21, 20, 1);
			setData(24, 22, 20, 1);
			setData(24, 22, 19, 1);
			setData(24, 22, 18, 1);
			setData(25, 22, 18, 1);
			setData(26, 21, 18, 1);
			setData(27, 20, 18, 1);
			setData(28, 17, 17, 1);
			setData(28, 17, 18, 1);
			setData(28, 17, 19, 1);
			setData(27, 17, 17, 1);
			setData(27, 17, 18, 1);
			setData(27, 17, 19, 1);
			setData(29, 17, 17, 1);
			setData(29, 17, 18, 1);
			setData(29, 17, 19, 1);
		#pragma endregion

		#pragma region firstMap
			setData(20, 30, 30, 1);
			setData(21, 30, 30, 1);
			setData(22, 30, 30, 1);
			setData(23, 30, 30, 1);
			setData(24, 30, 30, 1);
			setData(20, 30, 31, 1);
			setData(21, 30, 31, 1);
			setData(22, 30, 31, 1);
			setData(23, 30, 31, 1);
			setData(24, 30, 31, 1);
			setData(20, 30, 32, 1);
			setData(21, 30, 32, 1);
			setData(22, 30, 32, 1);
			setData(23, 30, 32, 1);
			setData(24, 30, 32, 1);
			setData(20, 30, 33, 1);
			setData(21, 30, 33, 1);
			setData(22, 30, 33, 1);
			setData(23, 30, 33, 1);
			setData(24, 30, 33, 1);
			setData(20, 30, 34, 1);
			setData(21, 30, 34, 1);
			setData(22, 30, 34, 1);
			setData(23, 30, 34, 1);
			setData(24, 30, 34, 1);
			setData(25, 30, 32, 1);
			setData(26, 30, 32, 1);
			setData(27, 30, 32, 1);
			setData(28, 30, 32, 1);
			setData(28, 30, 33, 1);
			setData(28, 30, 34, 1);
			setData(28, 30, 35, 1);
			setData(28, 30, 36, 1);
			setData(28, 30, 37, 1);
			setData(27, 30, 37, 1);
			setData(26, 30, 37, 1);
			setData(25, 30, 37, 1);
			setData(24, 30, 37, 1);
			setData(23, 30, 37, 1);
			setData(22, 30, 37, 1);
			setData(21, 30, 37, 1);
			setData(21, 30, 36, 1);

		#pragma endregion

#pragma region fourthMap
			setData(40, 40, 40, 1);
			setData(40, 40, 39, 1);
			setData(40, 41, 38, 1);
			setData(40, 42, 37, 1);
			setData(40, 40, 36, 1);

			setData(40, 41, 35, 1);
			setData(40, 42, 34, 1);
			setData(40, 43, 33, 1);
			setData(40, 44, 32, 1);
			setData(40, 45, 31, 1);
			setData(40, 46, 30, 1);
			setData(40, 47, 29, 1);

			setData(41, 48, 29, 1);
			setData(42, 49, 29, 1);
			setData(43, 50, 29, 1);
			setData(44, 51, 29, 1);
			setData(45, 52, 29, 1);
			setData(46, 53, 29, 1);
			setData(47, 54, 29, 1);

			setData(47, 55, 30, 1);
			setData(47, 56, 31, 1);
			setData(47, 57, 32, 1);
			setData(47, 58, 33, 1);
			setData(47, 59, 34, 1);
			setData(47, 60, 35, 1);
			setData(47, 61, 36, 1);

			setData(46, 62, 36, 1);
			setData(45, 63, 36, 1);
			setData(44, 64, 36, 1);
			setData(43, 65, 36, 1);

			setData(43, 65, 37, 1);
			setData(43, 65, 38, 1);
			setData(43, 65, 39, 1);
			setData(42, 65, 39, 1);
			setData(44, 65, 39, 1);

			setData(44, 55, 40, 1);
			setData(44, 55, 41, 1);
			setData(44, 55, 42, 1);
			setData(44, 55, 43, 1);

			setData(42, 50, 40, 1);
			setData(43, 50, 40, 1);
			setData(44, 50, 40, 1);
			setData(41, 50, 40, 1);
			setData(45, 50, 40, 1);
			setData(41, 50, 39, 1);
			setData(42, 50, 39, 1);
			setData(43, 50, 39, 1);
			setData(44, 50, 39, 1);
			setData(45, 50, 39, 1);
			setData(41, 50, 38, 1);
			setData(42, 50, 38, 1);
			setData(43, 50, 38, 1);
			setData(44, 50, 38, 1);
			setData(45, 50, 38, 1);

			setData(43, 50, 38, 1);
			setData(43, 50, 37, 1);
			setData(43, 50, 36, 1);
			setData(43, 50, 35, 1);
			setData(43, 50, 34, 1);
			setData(43, 50, 33, 1);
			setData(43, 50, 32, 1);
			setData(43, 50, 31, 1);
			setData(43, 50, 30, 1);

#pragma endregion

	#pragma endregion
	
	std::vector<glm::vec3> posList;

	// convert map data into vec3 list
	for (std::map<coord, int>::iterator idata = mData.begin(); idata != mData.end(); idata++)
	{
		if(idata->second == 1)
		{
			posList.push_back(getPosition(idata->first));
		}
	}

	// create vertices
	for(int posIdx = 0; posIdx < posList.size(); posIdx++)
	{
		for (int verIdx = 0; verIdx < VERTICES_LENGTH; verIdx += 6) {
			glm::vec3 vertex;
			vertex.x = cubeVertices[verIdx] * 0.5 + posList[posIdx].x;
			vertex.y = cubeVertices[verIdx + 1] * 0.5 + posList[posIdx].y;
			vertex.z = cubeVertices[verIdx + 2] * 0.5 + posList[posIdx].z;
			mVertices.push_back(vertex);
			glm::vec3 normal;
			normal.x = cubeVertices[verIdx + 3];
			normal.y = cubeVertices[verIdx + 4];
			normal.z = cubeVertices[verIdx + 5];
			mVertices.push_back(normal);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind buffer
	glBindVertexArray(0);

}

void GameMap::draw()
{
	// Bind shader (map.vert / map.frag)
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

		// set uniforms
		if (mLightPtr != nullptr)
			mLightPtr->setUniform(*mShaderPtr);

		if (mMaterialPtr != nullptr)
			mMaterialPtr->setUniform(*mShaderPtr);
	}
	
	// Bind texture
	if (mMaterialPtr != nullptr)
		mMaterialPtr->bind();

	// Draw
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size() / 2);
	glBindVertexArray(0);

	// Unbind texture
	if (mMaterialPtr != nullptr)
		mMaterialPtr->unbind();

	// Unbind shader
	if (mShaderPtr != nullptr)
		mShaderPtr->unbind();
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

coord GameMap::key(int x, int y, int z) {
	return coord{ x, y, z};
}

glm::vec3 GameMap::getPosition(int x, int y, int z)
{
	glm::vec3 result;

	result.z = (float)z + mDefaultPos.z;
	result.y = (float)y + mDefaultPos.y;
	result.x = (float)x + mDefaultPos.x;

	return result;
}

glm::vec3 GameMap::getPosition(coord keyValue)
{
	return getPosition(keyValue.x, keyValue.y, keyValue.z);
}

