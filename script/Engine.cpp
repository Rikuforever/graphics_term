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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			// background color
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);

	// Initialize variables
	mLastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	
	// Load Resources
	mShaderPlayer.loadShaders("shaders/player.vert", "shaders/player.frag");
	mShaderMap.loadShaders("shaders/map.vert", "shaders/map.frag");
	mTexture.loadTexture("textures/wooden_crate.jpg", true);


	// Set Player Object
	mObjPlayer.bindEngine(this);						// bind 
	mObjPlayer.bindShader(mShaderPlayer);
	mObjPlayer.bindMaterial(mMaterialPlayer);
	mObjPlayer.bindLight(mLightDir);
	mObjPlayer.load();									// load
	mObjPlayer.scale = glm::vec3(0.5f, 0.5f, 0.5f);		// scale
	// Set Player Material
	mMaterialPlayer.ambient = glm::vec3(0.1f, 0.35f, 0.1f);
	mMaterialPlayer.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	mMaterialPlayer.specular = glm::vec3(0.45f, 0.55f, 0.45f);
	mMaterialPlayer.shininess = 32.0f;
	mMaterialPlayer.bindTexture(mTexture);

	// Set Map Object
	mObjMap.bindEngine(this);							// bind
	mObjMap.bindShader(mShaderMap);
	mObjMap.bindMaterial(mMaterialMap);
	mObjMap.bindLight(mLightDir);
	mObjMap.load();										// load
	// Set Map Material
	mMaterialMap.ambient = glm::vec3(0.1f, 0.35f, 0.1f);
	mMaterialMap.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	mMaterialMap.specular = glm::vec3(0.45f, 0.55f, 0.45f);
	mMaterialMap.shininess = 32.0f;


	// Set Camera
	mCam.setPosition(mObjPlayer.position + glm::vec3(10.0f, 10.0f, 10.0f));
	mCam.setLookAt(mObjPlayer.position);

	// Set Directional Light
	mLightDir.direction = glm::vec3(-1.0f, -2.0f, -3.0f);
	mLightDir.ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	mLightDir.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mLightDir.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	// Set Starting Point
	mapdata = &mObjMap;
	SetOffset(pcube,1, 1, 10);

	return true;
}

void Engine::update()
{
	// get delta time
	mCurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double deltaTime = mCurrentTime - mLastTime;

	// get key
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
	else if (keyStates['f'] || keyStates['F']) {
		keymode = 'f';
	}
	else {
		keymode = 'l';
	}

	// update	
	glm::vec3 previousPosition = glm::vec3(mObjPlayer.position);

	#pragma region player behavior
    RespawnCheck(pcube);
	Gravity(pcube);
	DefineCubeLine(pcube);
	Move(pcube);
	if(keymode=='f')
	DebugLog(pcube);
	
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

	#pragma endregion 

	#pragma region cube color (diffuse) change
	static float timer = 0;

	if (timer >= 1.0) {
		timer = 0;
		if (mMaterialPlayer.diffuse.x == 1.0 && mMaterialPlayer.diffuse.y == 0.0 && mMaterialPlayer.diffuse.z == 0.0) {
			mMaterialPlayer.diffuse.x = 1.0;
			mMaterialPlayer.diffuse.y = 0.5;
			mMaterialPlayer.diffuse.z = 0.0;
		}
		else if (mMaterialPlayer.diffuse.x == 1.0 && mMaterialPlayer.diffuse.y == 0.5 && mMaterialPlayer.diffuse.z == 0.0) {
			mMaterialPlayer.diffuse.x = 1.0;
			mMaterialPlayer.diffuse.y = 1.0;
			mMaterialPlayer.diffuse.z = 0.0;
		}
		else if (mMaterialPlayer.diffuse.x == 1.0 && mMaterialPlayer.diffuse.y == 1.0 && mMaterialPlayer.diffuse.z == 0.0) {
			mMaterialPlayer.diffuse.x = 0.0;
			mMaterialPlayer.diffuse.y = 1.0;
			mMaterialPlayer.diffuse.z = 0.0;
		}
		else if (mMaterialPlayer.diffuse.x == 0.0 && mMaterialPlayer.diffuse.y == 1.0 && mMaterialPlayer.diffuse.z == 0.0) {
			mMaterialPlayer.diffuse.x = 0.0;
			mMaterialPlayer.diffuse.y = 1.0;
			mMaterialPlayer.diffuse.z = 1.0;
		}
		else if (mMaterialPlayer.diffuse.x == 0.0 && mMaterialPlayer.diffuse.y == 1.0 && mMaterialPlayer.diffuse.z == 1.0) {
			mMaterialPlayer.diffuse.x = 0.0;
			mMaterialPlayer.diffuse.y = 0.0;
			mMaterialPlayer.diffuse.z = 1.0;
		}
		else if (mMaterialPlayer.diffuse.x == 0.0 && mMaterialPlayer.diffuse.y == 0.0 && mMaterialPlayer.diffuse.z == 1.0) {
			mMaterialPlayer.diffuse.x = 1.0;
			mMaterialPlayer.diffuse.y = 0.0;
			mMaterialPlayer.diffuse.z = 1.0;
		}
		else if (mMaterialPlayer.diffuse.x == 1.0 && mMaterialPlayer.diffuse.y == 0.0 && mMaterialPlayer.diffuse.z == 1.0) {
			mMaterialPlayer.diffuse.x = 1.0;
			mMaterialPlayer.diffuse.y = 0.0;
			mMaterialPlayer.diffuse.z = 0.0;
		}

	}
	else {
		timer += deltaTime;
	}
#pragma endregion

	mCam.move(mObjPlayer.position - previousPosition);	// camera follows player
}

void Engine::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// render
	mObjPlayer.draw();
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
