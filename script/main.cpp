#include <iostream>
#include <sstream>
#include <string>

#include "GL\glut.h"
#include "GL\GLU.H"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

// Global Variables
const char* APP_TITLE = "¤·¤²¤·";
int gWindow;
int gWindowWidth = 1024;
int gWindowHeight = 768;
bool gWireframe = false;

// Function prototypes
bool initOpenGL(int argc, char** argv);
void showFPS();



#pragma region CallBacks

void display(void){
	glClearDepth(1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw here

	showFPS();
	glutSwapBuffers();
}

void reshape(int w, int h){
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

void mouseClick(GLint button, GLint state, GLint x, GLint y)
{
	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y)
{

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	}
	
	glutPostRedisplay();
}

void myIdle(void)
{
	glutPostRedisplay();
}


void TimerFunc(int value)
{	
	glutPostRedisplay();
	glutTimerFunc(1, TimerFunc, 1);
}

#pragma endregion 

int main(int argc, char** argv) {
	if(!initOpenGL(argc, argv))
	{
		std::cerr << "GLUT initialization failed" << std::endl;
		return -1;
	}

	glutMainLoop();
}

bool initOpenGL(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(gWindowWidth, gWindowHeight);

	// Create Window
	gWindow = glutCreateWindow(APP_TITLE);
	if(gWindow == NULL)
	{
		std::cerr << "Failed to create GLUT window" << std::endl;
		return false;
	}

	// Set the required callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, TimerFunc, 1);
	glutIdleFunc(myIdle);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);

	return true;
}

void showFPS()
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glutGet(GLUT_ELAPSED_TIME);

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text update to 4 times per second
	if(elapsedSeconds > 250.0)
	{
		previousSeconds = currentSeconds;
		double fps = 1000.0 * (double)frameCount / elapsedSeconds;
		double msPerFrame = 1.0 / fps;

		// The C++ way of setting the window title
		std::ostringstream outs;
		outs.precision(3);	// decimal places
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glutSetWindowTitle(outs.str().c_str());

		// Reset for next average
		frameCount = 0;
	}

	frameCount++;
}