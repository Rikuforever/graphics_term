#include "Engine.h"

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
	mLightDir.ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	mLightDir.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	mLightDir.specular = glm::vec3(1.0f, 1.0f, 1.0f);


	// Set objects
	mObjFloor.position = glm::vec3(0.0f, -1.0f, 0.0f);
	mObjFloor.scale = glm::vec3(10.0f, 0.01f, 10.0f);

	// Construct Map
#pragma region MapData

#pragma region mainmap
	mObjMap.setData( 0, 0, 10, 1);
	mObjMap.setData( 0, 1, 10, 1);
	mObjMap.setData( 0, 2, 10, 1);
	mObjMap.setData( 0, 3, 10, 1);
	mObjMap.setData( 0, 3,  9, 1);
	mObjMap.setData( 0, 3, 11, 1);
	mObjMap.setData( 1, 0, 10, 1);
	mObjMap.setData( 2, 0, 10, 1);
	mObjMap.setData( 3, 0, 10, 1);
	mObjMap.setData( 4, 0, 10, 1);
	mObjMap.setData( 5, 0, 10, 1);
	mObjMap.setData( 6, 0, 10, 1);
	mObjMap.setData( 7, 1, 10, 1);
	mObjMap.setData( 8, 2, 10, 1);
	mObjMap.setData( 9, 3, 10, 1);
	mObjMap.setData( 9, 4,  9, 1);
	mObjMap.setData( 9, 5,  8, 1);
	mObjMap.setData( 9, 6,  7, 1);
	mObjMap.setData( 9, 6,  6, 1);
	mObjMap.setData( 9, 6,  5, 1);
	mObjMap.setData( 9, 6,  4, 1);
	mObjMap.setData( 9, 6,  3, 1);
	mObjMap.setData( 8, 7,  3, 1);
	mObjMap.setData( 7, 8,  3, 1);
	mObjMap.setData( 6, 9,  3, 1);
	mObjMap.setData( 5, 10, 3, 1);
	mObjMap.setData( 4, 10, 3, 1);
	mObjMap.setData( 3, 10, 3, 1);
	mObjMap.setData( 2, 10, 3, 1);
	mObjMap.setData( 1, 10, 3, 1);
	mObjMap.setData( 0, 10, 3, 1);
	mObjMap.setData( 0, 9,  4, 1);
	mObjMap.setData( 0, 8,  5, 1);
	mObjMap.setData( 0, 7,  6, 1);
	mObjMap.setData( 0, 6,  7, 1);
	mObjMap.setData( 0, 6,  8, 1);
	mObjMap.setData( 0, 6,  9, 1);
#pragma endregion
#pragma region root2
	mObjMap.setData(  4, 1, 11, 1);
	mObjMap.setData(  4, 2, 12, 1);
	mObjMap.setData(  4, 3, 13, 1);
	mObjMap.setData(  4, 4, 14, 1);
	mObjMap.setData(  5, 3, 14, 1);
	mObjMap.setData(  6, 2, 14, 1);
	mObjMap.setData(  7, 1, 14, 1);
	mObjMap.setData(  8, 1, 14, 1);
	mObjMap.setData(  9, 1, 14, 1);
	mObjMap.setData( 10, 1, 14, 1);
	mObjMap.setData( 11, 1, 14, 1);
	mObjMap.setData( 11, 1, 13, 1);
	mObjMap.setData( 11, 1, 12, 1);
	mObjMap.setData( 12, 1, 12, 1);
	mObjMap.setData( 12, 1, 11, 1);
	mObjMap.setData( 12, 1, 10, 1);
	mObjMap.setData( 13, 1, 10, 1);
	mObjMap.setData( 13, 1,  9, 1);
	mObjMap.setData( 13, 1,  8, 1);
	mObjMap.setData( 14, 1,  8, 1);
	mObjMap.setData( 14, 1,  7, 1);
	mObjMap.setData( 14, 1,  6, 1);
	mObjMap.setData( 14, 2,  6, 1);
	mObjMap.setData( 13, 3,  6, 1);
	mObjMap.setData( 12, 4,  6, 1);
	mObjMap.setData( 11, 5,  6, 1);
	mObjMap.setData( 10, 6,  6, 1);
#pragma endregion
#pragma region trashmap
	mObjMap.setData( 1,  1, 11, 1);
	mObjMap.setData( 1,  1,  9, 1);
	mObjMap.setData( 2,  1, 11, 1);
	mObjMap.setData( 2,  1,  9, 1);
	mObjMap.setData( 3,  1, 11, 1);
	mObjMap.setData( 3,  1,  9, 1);
	mObjMap.setData( 4,  1,  9, 1);
	mObjMap.setData( 5,  1, 11, 1);
	mObjMap.setData( 5,  1,  9, 1);
	mObjMap.setData( 6,  1, 11, 1);
	mObjMap.setData( 6,  1,  9, 1);
	mObjMap.setData( 7,  2, 11, 1);
	mObjMap.setData( 7,  2,  9, 1);
	mObjMap.setData( 8,  3, 11, 1);
	mObjMap.setData( 8,  3,  9, 1);
	mObjMap.setData( 9,  7,  2, 1);
	mObjMap.setData( 9,  8,  2, 1);
	mObjMap.setData( 6, 10,  2, 1);
	mObjMap.setData( 6, 11,  2, 1);
	mObjMap.setData( 7,  9,  2, 1);
	mObjMap.setData( 7, 10,  2, 1);
	mObjMap.setData( 8,  8,  2, 1);
	mObjMap.setData( 8,  9,  2, 1);
	mObjMap.setData( 5, 11,  2, 1);
	mObjMap.setData( 5, 12,  2, 1);
	mObjMap.setData( 4, 11,  2, 1);
	mObjMap.setData( 4, 12,  2, 1);
	mObjMap.setData( 3, 11,  2, 1);
	mObjMap.setData( 3, 12,  2, 1);
	mObjMap.setData( 2, 11,  2, 1);
	mObjMap.setData( 2, 12,  2, 1);
	mObjMap.setData( 1, 11,  2, 1);
	mObjMap.setData( 1, 12,  2, 1);
	mObjMap.setData( 0, 11,  2, 1);
	mObjMap.setData( 0, 12,  2, 1);
	mObjMap.setData( 6, 12,  2, 1);
	mObjMap.setData( 7, 11,  2, 1);
	mObjMap.setData( 7, 12,  2, 1);
	mObjMap.setData( 8, 12,  2, 1);
	mObjMap.setData( 8, 11,  2, 1);
	mObjMap.setData( 8, 10,  2, 1);
	mObjMap.setData( 9, 12,  2, 1);
	mObjMap.setData( 9, 11,  2, 1);
	mObjMap.setData( 9, 10,  2, 1);
	mObjMap.setData( 9,  9,  2, 1);
#pragma endregion

#pragma region secondMap
	mObjMap.setData(20, 20, 20, 1);
	mObjMap.setData(20, 20, 19, 1);
	mObjMap.setData(20, 20, 21, 1);
	mObjMap.setData(19, 20, 20, 1);
	mObjMap.setData(19, 20, 19, 1);
	mObjMap.setData(19, 20, 21, 1);
	mObjMap.setData(21, 20, 20, 1);
	mObjMap.setData(22, 20, 20, 1);
	mObjMap.setData(23, 21, 20, 1);
	mObjMap.setData(24, 22, 20, 1);
	mObjMap.setData(24, 22, 19, 1);
	mObjMap.setData(24, 22, 18, 1);
	mObjMap.setData(25, 22, 18, 1);
	mObjMap.setData(26, 21, 18, 1);
	mObjMap.setData(27, 20, 18, 1);
	mObjMap.setData(28, 17, 17, 1);
	mObjMap.setData(28, 17, 18, 1);
	mObjMap.setData(28, 17, 19, 1);
	mObjMap.setData(27, 17, 17, 1);
	mObjMap.setData(27, 17, 18, 1);
	mObjMap.setData(27, 17, 19, 1);
	mObjMap.setData(29, 17, 17, 1);
	mObjMap.setData(29, 17, 18, 1);
	mObjMap.setData(29, 17, 19, 1);
#pragma endregion

#pragma region firstMap
	mObjMap.setData(20, 30, 30, 1);
	mObjMap.setData(21, 30, 30, 1);
	mObjMap.setData(22, 30, 30, 1);
	mObjMap.setData(23, 30, 30, 1);
	mObjMap.setData(24, 30, 30, 1);
	mObjMap.setData(20, 30, 31, 1);
	mObjMap.setData(21, 30, 31, 1);
	mObjMap.setData(22, 30, 31, 1);
	mObjMap.setData(23, 30, 31, 1);
	mObjMap.setData(24, 30, 31, 1);
	mObjMap.setData(20, 30, 32, 1);
	mObjMap.setData(21, 30, 32, 1);
	mObjMap.setData(22, 30, 32, 1);
	mObjMap.setData(23, 30, 32, 1);
	mObjMap.setData(24, 30, 32, 1);
	mObjMap.setData(20, 30, 33, 1);
	mObjMap.setData(21, 30, 33, 1);
	mObjMap.setData(22, 30, 33, 1);
	mObjMap.setData(23, 30, 33, 1);
	mObjMap.setData(24, 30, 33, 1);
	mObjMap.setData(20, 30, 34, 1);
	mObjMap.setData(21, 30, 34, 1);
	mObjMap.setData(22, 30, 34, 1);
	mObjMap.setData(23, 30, 34, 1);
	mObjMap.setData(24, 30, 34, 1);
	mObjMap.setData(25, 30, 32, 1);
	mObjMap.setData(26, 30, 32, 1);
	mObjMap.setData(27, 30, 32, 1);
	mObjMap.setData(28, 30, 32, 1);
	mObjMap.setData(28, 30, 33, 1);
	mObjMap.setData(28, 30, 34, 1);
	mObjMap.setData(28, 30, 35, 1);
	mObjMap.setData(28, 30, 36, 1);
	mObjMap.setData(28, 30, 37, 1);
	mObjMap.setData(27, 30, 37, 1);
	mObjMap.setData(26, 30, 37, 1);
	mObjMap.setData(25, 30, 37, 1);
	mObjMap.setData(24, 30, 37, 1);
	mObjMap.setData(23, 30, 37, 1);
	mObjMap.setData(22, 30, 37, 1);
	mObjMap.setData(21, 30, 37, 1);
	mObjMap.setData(21, 30, 36, 1);

#pragma endregion

#pragma endregion
	mObjMap.load();
	// Set Map
	mMaterialMap.ambient = glm::vec3(0.1f, 0.35f, 0.1f);
	mMaterialMap.diffuse = glm::vec3(1.0f, 0.0f, 0.0f);
	mMaterialMap.specular = glm::vec3(0.45f, 0.55f, 0.45f);
	mMaterialMap.shininess = 32.0f;
	return true;
}

void Engine::update()
{
	mCurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double deltaTime = mCurrentTime - mLastTime;

	// update	
	glm::vec3 previousPosition = glm::vec3(mObjPlayer.position);

	if (keyStates['a'] || keyStates['A'])
		mObjPlayer.position.x -= (float)(deltaTime * 5.0f);
	if (keyStates['d'] || keyStates['D']) 
		mObjPlayer.position.x += (float)(deltaTime * 5.0f);
	if (keyStates['w'] || keyStates['W'])
		mObjPlayer.position.z -= (float)(deltaTime * 5.0f);
	if (keyStates['s'] || keyStates['S'])
		mObjPlayer.position.z += (float)(deltaTime * 5.0f);
	if (keyStates['q'] || keyStates['Q'])
		mObjPlayer.position.y += (float)(deltaTime * 5.0f);
	if (keyStates['e'] || keyStates['E'])
		mObjPlayer.position.y -= (float)(deltaTime * 5.0f);

	mCam.move(mObjPlayer.position - previousPosition);

	//cube color (diffuse) change
#pragma region cube color (diffuse) change
	static float timer = 0;

	if (timer >= 1.0) {
		timer = 0;
		if (mMaterialMap.diffuse.x == 1.0 && mMaterialMap.diffuse.y == 0.0 && mMaterialMap.diffuse.z == 0.0) {
			mMaterialMap.diffuse.x = 1.0;
			mMaterialMap.diffuse.y = 0.5;
			mMaterialMap.diffuse.z = 0.0;
		}
		else if (mMaterialMap.diffuse.x == 1.0 && mMaterialMap.diffuse.y == 0.5 && mMaterialMap.diffuse.z == 0.0) {
			mMaterialMap.diffuse.x = 1.0;
			mMaterialMap.diffuse.y = 1.0;
			mMaterialMap.diffuse.z = 0.0;
		}
		else if (mMaterialMap.diffuse.x == 1.0 && mMaterialMap.diffuse.y == 1.0 && mMaterialMap.diffuse.z == 0.0) {
			mMaterialMap.diffuse.x = 0.0;
			mMaterialMap.diffuse.y = 1.0;
			mMaterialMap.diffuse.z = 0.0;
		}
		else if (mMaterialMap.diffuse.x == 0.0 && mMaterialMap.diffuse.y == 1.0 && mMaterialMap.diffuse.z == 0.0) {
			mMaterialMap.diffuse.x = 0.0;
			mMaterialMap.diffuse.y = 1.0;
			mMaterialMap.diffuse.z = 1.0;
		}
		else if (mMaterialMap.diffuse.x == 0.0 && mMaterialMap.diffuse.y == 1.0 && mMaterialMap.diffuse.z == 1.0) {
			mMaterialMap.diffuse.x = 0.0;
			mMaterialMap.diffuse.y = 0.0;
			mMaterialMap.diffuse.z = 1.0;
		}
		else if (mMaterialMap.diffuse.x == 0.0 && mMaterialMap.diffuse.y == 0.0 && mMaterialMap.diffuse.z == 1.0) {
			mMaterialMap.diffuse.x = 1.0;
			mMaterialMap.diffuse.y = 0.0;
			mMaterialMap.diffuse.z = 1.0;
		}
		else if (mMaterialMap.diffuse.x == 1.0 && mMaterialMap.diffuse.y == 0.0 && mMaterialMap.diffuse.z == 1.0) {
			mMaterialMap.diffuse.x = 1.0;
			mMaterialMap.diffuse.y = 0.0;
			mMaterialMap.diffuse.z = 0.0;
		}

	}
	else {
		timer += deltaTime;
	}
#pragma endregion



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
