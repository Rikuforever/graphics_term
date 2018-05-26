#include "Engine.h"
#include "Player.h"


#include "GL/glut.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::init()
{
	// Define the viewport dimensions
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);

	// Initialize variables
	mLastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	
	// Load resources
	mShaderPlayer.loadShaders("shaders/basic.vert", "shaders/basic.frag");
	mShaderMap.loadShaders("shaders/map.vert", "shaders/map.frag");
	mTexture1.loadTexture("textures/wooden_crate.jpg", true);
	mTexture2.loadTexture("textures/grid.jpg", true);
	mObjPlayer.load();
	mObjFloor.load();

	// Bind resources
	mObjPlayer.bindEngine(this);			// player
	mObjPlayer.bindShader(mShaderPlayer);
	mObjPlayer.bindTexture(mTexture1);
	mObjFloor.bindEngine(this);				// floor
	mObjFloor.bindShader(mShaderPlayer);
	mObjFloor.bindTexture(mTexture2);
	mObjMap.bindEngine(this);				// map
	mObjMap.bindShader(mShaderMap);
	mObjMap.bindLight(mLightDir);
	mObjMap.bindMaterial(mMaterialMap);

	// Set scene
	mCam.setPosition(mObjPlayer.position + glm::vec3(10.0f, 10.0f, 10.0f));
	mCam.setLookAt(mObjPlayer.position);
	mLightDir.direction = glm::vec3(-1.0f, -2.0f, -3.0f);
	mLightDir.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	mLightDir.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mLightDir.specular = glm::vec3(1.0f, 1.0f, 1.0f);


	// Set objects
	mObjFloor.position = glm::vec3(0.0f, -1.0f, 0.0f);
	mObjFloor.scale = glm::vec3(10.0f, 0.01f, 10.0f);

	// Construct Map
	mObjMap.setData(0, 0, 0, 1);
	mObjMap.setData(1, 0, 0, 1);
	mObjMap.setData(0, 1, 0, 1);
	mObjMap.setData(0, 0, 1, 1);
	mObjMap.load();
	// Set Map
	mMaterialMap.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
	mMaterialMap.diffuse = glm::vec3(0.6f, 0.0f, 0.0f);
	mMaterialMap.specular = glm::vec3(0.8f, 0.8f, 0.8f);
	mMaterialMap.shininess = 500.0f;

	mapdata = &mObjMap;

	return true;
}

void Engine::update()
{
	mCurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double deltaTime = mCurrentTime - mLastTime;

	// update	
	glm::vec3 previousPosition = glm::vec3(mObjPlayer.position);
	
	if (keyStates['d'] || keyStates['D']) {
		keymode = 'd';
	}
	else if (keyStates['w'] || keyStates['W']) {
		keymode = 'w';
	}
	else if (keyStates['a'] || keyStates['A']) {
		keymode = 'a';
	}
	else if (keyStates['s'] || keyStates['S']) {
		keymode = 's';
	}
	else {
		keymode = 'f';
	}
	/*
	if (keyStates['a'] || keyStates['A'])
		mObjPlayer.position.x -= (float)(deltaTime * 5.0f);
	if (keyStates['d'] || keyStates['D']) 
		mObjPlayer.position.x += (float)(deltaTime * 5.0f);
	if (keyStates['w'] || keyStates['W'])
		mObjPlayer.position.z -= (float)(deltaTime * 5.0f);
	if (keyStates['s'] || keyStates['S'])
		mObjPlayer.position.z += (float)(deltaTime * 5.0f);
	*/
	
	DefineCubeLine(pcube);
	Move(pcube);
	mObjPlayer.position = pcube->position;
	int rnum = (int)(cube.full_z_angle / 90) % 4;
	switch (rnum) {
	case 0:
		mObjPlayer.rotation = glm::vec3(cube.full_z_angle, 0.0f, -cube.full_x_angle);
		break;
	case 1:
		mObjPlayer.rotation = glm::vec3(cube.full_z_angle, -cube.full_x_angle, 0.0f);
		break;
	case 2:
		mObjPlayer.rotation = glm::vec3(cube.full_z_angle, 0.0f, cube.full_x_angle);
		break;
	case 3:
		mObjPlayer.rotation = glm::vec3(cube.full_z_angle, cube.full_x_angle, 0.0f);
		break;
	}

	mCam.move(mObjPlayer.position - previousPosition);

	// mCam.setPosition(mObjPlayer.position + glm::vec3(10.0f, 10.0f, -10.0f));
	// mCam.setLookAt(mObjPlayer.position);

}

void Engine::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// render
	mObjPlayer.draw();
	//mObjFloor.draw();
	mObjMap.draw();

	glutSwapBuffers();
	mLastTime = mCurrentTime;
}

void Engine::reshape(int w, int h)
{
	gWindowWidth = w;
	gWindowHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);	// switch matrix mode
	glLoadIdentity();

	if (w <= h)
		gluOrtho2D(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w);
	else
		gluOrtho2D(-2.0 * (GLfloat)w / (GLfloat)h, 2.0 * (GLfloat)w / (GLfloat)h, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);		// return to modelview mode
	glutPostRedisplay();
}

void Engine::mouseClick(GLint button, GLint state, GLint x, GLint y)
{
	glutPostRedisplay();
}

void Engine::mouseMotion(GLint x, GLint y)
{
	glutPostRedisplay();
}

void Engine::keyboard(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	glutPostRedisplay();
}

void Engine::keyboardUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
	glutPostRedisplay();
}

void Engine::specialKeyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_F1:
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}

}

void Engine::idle()
{
	glutPostRedisplay();
}

Camera Engine::getCamera()
{
	return mCam;
}
