#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <map>

#include "GL/glew.h"
#include "glm/glm.hpp"

using std::string;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	
	enum ShaderType
	{
		VERTEX,
		FRAGMENT,
		PROGRAM
	};

	bool loadShaders(const char* vsFilename, const char* fsFilename);
	void bind();
	void unbind();

	GLuint getProgram() const;

	void setUniform(const GLchar* name, const glm::vec2& v);
	void setUniform(const GLchar* name, const glm::vec3& v);
	void setUniform(const GLchar* name, const glm::vec4& v);
	void setUniform(const GLchar* name, const glm::mat4& m);
	void setUniform(const GLchar* name, const GLfloat f);
	void setUniform(const GLchar* name, const GLint v);

	GLint getUniformLocation(const GLchar* name);

private:
	string fileToString(const string& filename);
	void checkCompileErrors(GLuint shader, ShaderType type);

	GLuint mHandle;
	std::map<string, GLint> mUniformLocations;
};

#endif
