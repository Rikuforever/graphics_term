#include <stdlib.h>
#include <math.h>

#include <glut.h>
#include <gl\GLU.h>

#pragma region CallBacks

void display(void){
	glClearDepth(1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw here

	glutSwapBuffers();
}

void reshape(int w, int h){
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(-20, 20, -20, 20);
	glutPostRedisplay();
}

void myMouseClick(GLint button, GLint state, GLint x, GLint y)
{
	glutPostRedisplay();
}

void myMouseMotion(GLint x, GLint y)
{

}

void myKeyboard(unsigned char key, int x, int y)
{	
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

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutCreateWindow("PA_1");

	glutDisplayFunc(display);
	// glutReshapeFunc(reshape);
	glutMouseFunc(myMouseClick);
	glutMotionFunc(myMouseMotion);
	glutKeyboardFunc(myKeyboard);
	glutTimerFunc(100, TimerFunc, 1);
	glutIdleFunc(myIdle);

	glutMainLoop();
}