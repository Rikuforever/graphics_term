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
	mShader.loadShaders("shaders/basic.vert", "shaders/basic.frag");
	mTexture.loadTexture("textures/wooden_crate.jpg", true);
	mObj.load();

	// Bind resources
	mObj.bindWindow(gWindowWidth,gWindowHeight);
	mObj.bindShader(mShader);
	mObj.bindTexture(mTexture);

	return true;
}

void Engine::update()
{
	mCurrentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double deltaTime = mCurrentTime - mLastTime;

	// update
	mObj.position = glm::vec3(0.0f, 0.0f, -5.0f);
	mObj.rotation.x += (float)(deltaTime * 50.0f);
	if (mObj.rotation.x >= 360.0f) mObj.rotation.x = 0.0f;
	mObj.rotation.y += (float)(deltaTime * 50.0f);
	if (mObj.rotation.y >= 360.0f) mObj.rotation.y = 0.0f;
}

void Engine::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// render
	mObj.draw();

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
