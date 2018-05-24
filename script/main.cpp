#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"

#include "Engine.h"

// Global Variables
const char* APP_TITLE = "¤·¤²¤·";
int gWindow;

// Function prototypes
bool initOpenGL(int argc, char** argv);
void showFPS();
void display(void);
void reshape(int w, int h);
void mouseClick(GLint button, GLint state, GLint x, GLint y);
void mouseMotion(GLint x, GLint y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void idle(void);
void timer(int value);

Engine e;

int main(int argc, char** argv) {
	if(!initOpenGL(argc, argv))
	{
		std::cerr << "GLUT initialization failed" << std::endl;
		return -1;
	}
	
	e.init();

	glutMainLoop();
}

bool initOpenGL(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(e.gWindowWidth, e.gWindowHeight);

	// Create Window
	gWindow = glutCreateWindow(APP_TITLE);
	if(gWindow == NULL)
	{
		std::cerr << "Failed to create GLUT window" << std::endl;
		return false;
	}

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initalize GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialKeyboard);
	glutIdleFunc(idle);

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


#pragma region CallBacks

void display(void) {
	showFPS();
	
	e.update();
	e.render();
}

void reshape(int w, int h) {
	e.reshape(w, h);
}

void mouseClick(GLint button, GLint state, GLint x, GLint y) {
	e.mouseClick(button, state, x, y);
}

void mouseMotion(GLint x, GLint y) {
	e.mouseMotion(x, y);
}

void keyboard(unsigned char key, int x, int y) {
	e.keyboard(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y)
{
	e.keyboardUp(key, x, y);
}

void specialKeyboard(int key, int x, int y)
{
	e.specialKeyboard(key, x, y);
}


void idle(void) {
	e.idle();
}

#pragma endregion 