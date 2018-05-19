#ifndef ENGINE_H
#define ENGINE_H

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "GameObject.h"

class Engine
{
public:
	Engine();
	~Engine();

	// GLUT callbacks
	bool init();
	void update();
	void render();
	void reshape(int w, int h);
	void mouseClick(GLint button, GLint state, GLint x, GLint y);
	void mouseMotion(GLint x, GLint y);
	void keyboard(unsigned char key, int x, int y);
	void specialKeyboard(int key, int x, int y);
	void idle(void);

	// resolution
	int gWindowWidth = 1024;
	int gWindowHeight = 768;

	// debug
	bool gWireframe = false;

private:
	ShaderProgram mShader;
	Texture2D mTexture;

	GameObject mObj;

	// update
	double mCurrentTime;
	double mLastTime;

	// render

};

#endif
