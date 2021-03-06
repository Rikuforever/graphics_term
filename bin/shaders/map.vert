#version 330 core

layout (location = 0) in vec3 pos;		// in local coords
layout (location = 1) in vec3 normal;

uniform mat4 model;			// model matrix
uniform mat4 view;			// view matrix
uniform mat4 projection;	// projection matrix

out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(model * vec4(pos, 1.0f));
	Normal = mat3(transpose(inverse(model))) * normal;
	
	gl_Position = projection * view * model * vec4(pos, 1.0f);
}