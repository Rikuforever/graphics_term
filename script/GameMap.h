#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <map>
#include <vector>
#include "glm/glm.hpp"

#include "GameObject.h"

#define VERTICES_LENGTH 216

struct coord
{
	int x, y, z;

	bool operator == (const coord & o)
	{
		return x == o.x &&  y == o.y && z == o.z;
	}

	bool operator < (const coord &o) const
	{
		return x < o.x || (x == o.x && y < o.y) || (x == o.x && y == o.y && z < o.z);
	}
};

class GameMap : public GameObject {
public:
	GameMap();
	~GameMap();

	void load() override;
	void draw() override;

	int getData(int x, int y, int z);
	void setData(int x, int y, int z, int value);


private:
	std::map<coord, int> mData;
	glm::vec3 mDefaultPos;

	std::vector<glm::vec3> mVertices;

	coord key(int x, int y, int z);
	glm::vec3 getPosition(int x, int y, int z);
	glm::vec3 getPosition(coord keyValue);

	GLfloat cubeVertices[VERTICES_LENGTH] = {
		// position				// normal

		// front face
		-1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,
		1.0f, -1.0f,  1.0f,		0.0f, 0.0f, 1.0f,
		1.0f,  1.0f,  1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,	0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f, 1.0f,
		1.0f, -1.0f,  1.0f,		0.0f, 0.0f, 1.0f,
								
		// back face			
		-1.0f,  1.0f, -1.0f,	0.0f, 0.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,
		1.0f,  1.0f, -1.0f,		0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,	0.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f, -1.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f, -1.0f,
								
		// left face			
		-1.0f,  1.0f, -1.0f,	-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	-1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	-1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	-1.0f, 0.0f, 0.0f,
								
		// right face			
		1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,
		1.0f,  1.0f, -1.0f,		1.0f, 0.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		1.0f, 0.0f, 0.0f,
		1.0f, -1.0f,  1.0f,		1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		1.0f, 0.0f, 0.0f,
								
		// top face				
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		0.0f, 1.0f, 0.0f,
		1.0f,  1.0f, -1.0f,		0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	0.0f, 1.0f, 0.0f,
		1.0f,  1.0f,  1.0f,		0.0f, 1.0f, 0.0f,
								
		// bottom face			
		-1.0f, -1.0f,  1.0f,	0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, -1.0f, 0.0f,
		1.0f, -1.0f,  1.0f,		0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, -1.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, -1.0f, 0.0f,
	};

};

#endif