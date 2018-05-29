#ifndef ENGINE_H
#define ENGINE_H

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "GameObject.h"
#include "GameObject_OBJ.h"
#include "GameMap.h"
#include "SkyBox.h"

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
	
	// camera
	Camera mCam;
	float theta;

	// light
	DirLight mLightDir;
	float beta;
	
	// update
	double mCurrentTime;
	double mLastTime;

	// render

	// keyboard
	bool keyStates[256] = {false};

	// player
	GameObject mObjPlayer;
	ShaderProgram mShaderPlayer;
	Material mMaterialPlayer;
	Texture2D mTexturePlayer;
	double mPlayerColor;

	// map
	GameMap mObjMap;
	ShaderProgram mShaderMap;
	Material mMaterialMap;

	// flag
	GameObject mObjFlag1;
	GameObject mObjFlag2;
	GameObject mObjFlag3;
	GameObject mObjFlag4;
	Material mMaterialFlag;
	Texture2D mTextureFlag;

	// sky
	SkyBox mObjSky;
	ShaderProgram mShaderSky;
	Material mMaterialSky;
	Texture2D mTextureSky;

	// deco
	ShaderProgram mShaderDeco;
	GameObject_OBJ mObjDeco1;
	Material mMaterialDeco1;
	Texture2D mTextureDeco1;
};

#endif
