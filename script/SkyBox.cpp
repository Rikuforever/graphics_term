#include "SkyBox.h"

void SkyBox::load()
{
#pragma region CUBE DATA
	GLfloat vertices[] = {
		// position				// tex coords	// normal

		
		-1.0f,  1.0f,  1.0f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	// front face
		 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,

		
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,		0.0f, 0.0f, -1.0f,	// back face
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,	1.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,		0.0f, 0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,

		
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	// left face
		-1.0f, -1.0f,  1.0f,	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,

		
		 1.0f,  1.0f,  1.0f,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f,	// right face
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,	1.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,

		
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// top face
		 1.0f,  1.0f,  1.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,	1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,

		
		-1.0f, -1.0f,  1.0f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,	// bottom face
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,	1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,	0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,	1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);
	// Texture Coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// Normal Coord attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Unbind buffer
	glBindVertexArray(0);
}
