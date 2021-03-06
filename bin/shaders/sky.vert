#version 330 core

layout (location = 0) in vec3 pos;		// in local coords
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

out vec2 TexCoord;

void main()
{
	TexCoord = texCoord;

	gl_Position = projection * view * model * vec4(pos, 1.0f);
}