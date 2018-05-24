#ifndef ENGINE_H
#define ENGINE_H

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "GameObject.h"
#include "GameMap.h"

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
	void keyboardUp(unsigned char key, int x, int y);
	void specialKeyboard(int key, int x, int y);
	void idle(void);

	Camera getCamera();

	// resolution
	int gWindowWidth = 1024;
	int gWindowHeight = 768;

	// debug
	bool gWireframe = false;

private:
	ShaderProgram mShaderPlayer;
	ShaderProgram mShaderMap;
	Texture2D mTexture1;
	Texture2D mTexture2;
	Camera mCam;

	// objects
	GameObject mObjPlayer;
	GameObject mObjFloor;
	GameMap mObjMap;

	// update
	double mCurrentTime;
	double mLastTime;

	// render

	// keyboard
	bool keyStates[256] = {false};

};

#endif
