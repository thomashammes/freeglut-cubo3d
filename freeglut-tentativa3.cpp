#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
using namespace std;
//teste

GLfloat T = 0;

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void spin() {
	T = T + 0.5;
	if (T > 360)
		T = 0;
	glutPostRedisplay();
}

void myInit() {
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void face(GLfloat vA[], GLfloat vB[], GLfloat vC[], GLfloat vD[]) {
	glBegin(GL_POLYGON);
		glVertex3fv(vA);
		glVertex3fv(vB);
		glVertex3fv(vC);
		glVertex3fv(vD);
	glEnd();
}

void edge(GLfloat vA[], GLfloat vB[]) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3fv(vA);
	glVertex3fv(vB);
	glEnd();
}

void cubeWireframe(GLfloat v0[], GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat v5[], GLfloat v6[], GLfloat v7[]) {
	edge(v0, v1); // 1
	edge(v1, v2); // 2
	edge(v2, v3); // 3
	edge(v3, v0); // 4
	edge(v4, v5); // 5
	edge(v5, v6); // 6
	edge(v6, v7); // 7
	edge(v7, v4); // 8
	edge(v0, v4); // 9
	edge(v5, v1); // 10
	edge(v2, v6); // 11
	edge(v7, v3); // 12
}

void cube(GLfloat v0[], GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat v4[], GLfloat v5[], GLfloat v6[], GLfloat v7[]) {
	glColor3f(1, 0, 0);
	face(v0, v1, v2, v3); // front

	glColor3f(0, 1, 0);
	face(v4, v5, v6, v7); // back

	glColor3f(0, 0, 1);
	face(v0, v3, v7, v4); // left

	glColor3f(1, 0, 1);
	face(v1, v2, v6, v5); // right

	glColor3f(1, 1, 0);
	face(v0, v1, v5, v4); // top

	glColor3f(0, 1, 1);
	face(v3, v2, v6, v7); // bottom
}

void display() {

	GLfloat vertices[8][3] = {
		{-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5},
		{-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}, {-0.5, -0.5, -0.5}
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glRotatef(T, 1, 1, 0);

	glLineWidth(2);

	//cube(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7]);
	cubeWireframe(vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], vertices[6], vertices[7]);


	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Aula 2 Youtube: Cubo Girando");

	myInit();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);

	glutIdleFunc(spin);
	glutMainLoop();


	return 0;
}



/* AULA 1 YOUTUBE

void myInit() {
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(5);

	glBegin(GL_POLYGON);
		glVertex2f(-0.5, 0.5);
		glVertex2f(0.5, 0.5);
		glVertex2f(0.5, -0.5);
		glVertex2f(-0.5, -0.5);
	glEnd();


	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Aula 1 Youtube");

	myInit();

	glutDisplayFunc(display);

	glutMainLoop();


	return 0;
}
*/

/* CÓDIGO DO PROFESSOR AULA 1

#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
using namespace std;


void display();
void keyboard(unsigned char key, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(256, 256);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Desenhando uma linha");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0, 256, 0, 256, -1, 1);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(10, 10);
	glVertex2i(245, 245);
	glEnd();

	glFlush();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}
*/