#include <iostream>
#include <sstream>
#include <string>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GL/wglew.h"
#include "GL/glut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ShaderProgram.h"
#include "Texture2D.h"

// Global Variables
const char* APP_TITLE = "¤·¤²¤·";
int gWindow;
int gWindowWidth = 1024;
int gWindowHeight = 768;
bool gWireframe = false;

// Function prototypes
bool initOpenGL(int argc, char** argv);
void showFPS();
void display(void);
void reshape(int w, int h);
void mouseClick(GLint button, GLint state, GLint x, GLint y);
void mouseMotion(GLint x, GLint y);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void timer(int value);

#pragma region TEMP DATA

double lastTime;
float cubeAngle;
glm::vec3 cubePos = glm::vec3(0.0f, 0.0f, -5.0f);

ShaderProgram shaderProgram;
Texture2D texture;

GLuint vbo, vao;

GLfloat vertices[] = {
	// position		 // tex coords

	// front face
	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

	// back face
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

	// left face
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
	-1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	-1.0f, -1.0f,  1.0f, 1.0f, 0.0f,

	// right face
	1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,

	// top face
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
	1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f, 0.0f,

	// bottom face
	-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
	1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
};

#pragma endregion 

int main(int argc, char** argv) {
	if(!initOpenGL(argc, argv))
	{
		std::cerr << "GLUT initialization failed" << std::endl;
		return -1;
	}
	
	glGenBuffers(1, &vbo);					// Generate an empty vertex buffer on the GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0));
	glEnableVertexAttribArray(0);

	// Texture Coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

	texture.loadTexture("textures/wooden_crate.jpg", true);
	
	// Initialize
	lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	cubeAngle = 0.0f;

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
	//glutTimerFunc(1, TimerFunc, 1);
	glutIdleFunc(idle);

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


#pragma region CallBacks

void display(void) {
	showFPS();
	
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw here
	double currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	double deltaTime = currentTime - lastTime;
	
	texture.bind(0);

	glm::mat4 model, view, projection;

	// Update
	cubeAngle += (float)(deltaTime * 50.0f);
	if (cubeAngle >= 360.0f) cubeAngle = 0.0f;

	model = glm::translate(model, cubePos) * glm::rotate(model, glm::radians(cubeAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	
	glm::vec3 camPos(0.0f, 0.0f, 0.0f);
	glm::vec3 targetPos(0.0f, 0.0f, -1.0f);
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	view = glm::lookAt(camPos, camPos + targetPos, up);

	projection = glm::perspective(glm::radians(45.0f), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 100.0f);

	shaderProgram.use();

	shaderProgram.setUniform("model", model);
	shaderProgram.setUniform("view", view);
	shaderProgram.setUniform("projection", projection);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

	glutSwapBuffers();

	lastTime = currentTime;
}

void reshape(int w, int h) {
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

void mouseClick(GLint button, GLint state, GLint x, GLint y) {
	glutPostRedisplay();
}

void mouseMotion(GLint x, GLint y) {

}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
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

void idle(void) {
	glutPostRedisplay();
}


void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1, timer, 1);
}

#pragma endregion 