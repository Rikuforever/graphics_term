#ifndef GAMEOBJECT_OBJ_H
#define GAMEOBJECT_OBJ_H

#include <vector>
#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "GameObject.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class GameObject_OBJ : public GameObject
{
public:
	GameObject_OBJ();

	bool loadOBJ(const std::string& filename);
	void draw() override;

private:
	void initBuffers();

	bool mLoaded;
	std::vector<Vertex> mVertices;
};


#endif