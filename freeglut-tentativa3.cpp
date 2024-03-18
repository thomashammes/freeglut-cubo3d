#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include <vector>
using namespace std;

GLfloat vertices[8][3] = { // matriz com a posição X, Y e Z de cada vértice do cubo
{-0.5, 0.5, 0.5}, {0.5, 0.5, 0.5}, {0.5, -0.5, 0.5}, {-0.5, -0.5, 0.5},
{-0.5, 0.5, -0.5}, {0.5, 0.5, -0.5}, {0.5, -0.5, -0.5}, {-0.5, -0.5, -0.5}
};

GLfloat altVertices[8][3]; // matriz que recebe a alteração dos vértices para escalar, rotacionar, e deslocar o cubo

GLfloat xDegrees = 0, yDegrees = 0, zDegrees = 0; // graus de rotação

bool xAxisActivated = false; // liga/desliga a rotação do eixo X
bool yAxisActivated = false; // liga/desliga a rotação do eixo Y
bool zAxisActivated = false; // liga/desliga a rotação do eixo Z


void edge(GLfloat vA[], GLfloat vB[]) { // função que cria uma aresta
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES);
		glVertex3fv(vA);
		glVertex3fv(vB);
	glEnd();
}

void cubeWireframe(GLfloat cubeVerticesMatrix[][3]) { // funcção que cada aresta do cubo pegando a posição de cada vértice
	GLfloat* v0 = cubeVerticesMatrix[0];
	GLfloat* v1 = cubeVerticesMatrix[1];
	GLfloat* v2 = cubeVerticesMatrix[2];
	GLfloat* v3 = cubeVerticesMatrix[3];
	GLfloat* v4 = cubeVerticesMatrix[4];
	GLfloat* v5 = cubeVerticesMatrix[5];
	GLfloat* v6 = cubeVerticesMatrix[6];
	GLfloat* v7 = cubeVerticesMatrix[7];

	edge(v0, v1);
	edge(v1, v2);
	edge(v2, v3);
	edge(v3, v0);
	edge(v4, v5);
	edge(v5, v6);
	edge(v6, v7);
	edge(v7, v4);
	edge(v0, v4);
	edge(v5, v1);
	edge(v2, v6);
	edge(v7, v3);
}

void myInit() {
	glClearColor(0, 0, 0, 1); // define a cor do fundo
	glEnable(GL_DEPTH_TEST); // permite renderização 3d
}

void copyMatrix(GLfloat source[8][3], GLfloat(&destination)[8][3]) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 3; ++j) {
			destination[i][j] = source[i][j];
		}
	}
}

void xAxisRotation(bool activated, GLfloat(&vertices)[8][3], GLfloat(&altVertices)[8][3], GLfloat radiance) {
	if (activated) {
		for (int i = 0; i < 8; i++) {
			altVertices[i][0] = vertices[i][0];
			altVertices[i][1] = vertices[i][1] * cos(radiance) - vertices[i][2] * sin(radiance);
			altVertices[i][2] = vertices[i][1] * sin(radiance) + vertices[i][2] * cos(radiance);
		}
	}
}

void yAxisRotation(bool activated, GLfloat (&vertices)[8][3], GLfloat(&altVertices)[8][3], GLfloat radiance) {
	if (activated) {
		for (int i = 0; i < 8; i++) {
			altVertices[i][0] = vertices[i][2] * sin(radiance) + vertices[i][0] * cos(radiance);
			altVertices[i][1] = vertices[i][1];
			altVertices[i][2] = vertices[i][2] * sin(radiance) - vertices[i][0] * sin(radiance);
		}
	}
}

void zAxisRotation(bool activated, GLfloat(&vertices)[8][3], GLfloat(&altVertices)[8][3], GLfloat radiance) {

	if (activated) {
		for (int i = 0; i < 8; i++) {
			altVertices[i][0] = vertices[i][0] * cos(radiance) - vertices[i][1] * sin(radiance);
			altVertices[i][1] = vertices[i][0] * sin(radiance) + vertices[i][1] * cos(radiance);
			altVertices[i][2] = vertices[i][2];
		}
	}
}

void allAxisRotation(bool xActivated, bool yActivated, bool zActivated, GLfloat (&vertices)[8][3], GLfloat(&altVertices)[8][3]) {
	GLfloat tempVertices[8][3];
	GLfloat xRadiance = xDegrees * 3.14 / 180;
	GLfloat yRadiance = yDegrees * 3.14 / 180;
	GLfloat zRadiance = zDegrees * 3.14 / 180;
	xAxisRotation(xActivated, vertices, altVertices, xRadiance); // rotaciona o eixo X se ativado
	copyMatrix(altVertices, tempVertices);
	yAxisRotation(yActivated, tempVertices, altVertices, yRadiance); // rotaciona o eixo Y se ativado
	copyMatrix(altVertices, tempVertices);
	zAxisRotation(zActivated, tempVertices, altVertices, zRadiance); // rotaciona o eixo Z se ativado
}

void update(int value) {
	if (xAxisActivated) {
		xDegrees += 1;
	}
	if (yAxisActivated) {
		yDegrees += 1;
	}
	if (zAxisActivated) {
		zDegrees += 1;
	}
	glutPostRedisplay(); // Marca a janela para redesenhar
	glutTimerFunc(16, update, 0);
}

void translateCube(GLfloat x, GLfloat y, GLfloat z) { // desloca o cubo
	for (int i = 0; i < 8; ++i) {
		vertices[i][0] += x;
		vertices[i][1] += y;
		vertices[i][2] += z;
	}
}

void scaleCube(GLfloat scale) { // muda a escala do cubo
	for (int i = 0; i < 8; ++i) {
		vertices[i][0] *= scale;
		vertices[i][1] *= scale;
		vertices[i][2] *= scale;
	}
}


void keyboardControl(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'x':
	case 'X':
		if (xAxisActivated) xDegrees = 0;
		xAxisActivated = !xAxisActivated;
		break;
	case 'y':
	case 'Y':
		if (yAxisActivated) yDegrees = 0;
		yAxisActivated = !yAxisActivated;
		break;
	case 'z':
	case 'Z':
		if (zAxisActivated) zDegrees = 0;
		zAxisActivated = !zAxisActivated;
		break;
	case 'a':
	case 'A':
		translateCube(-0.1, 0.0, 0.0);
		break;
	case 'd':
	case 'D':
		translateCube(0.1, 0.0, 0.0);
		break;
	case 's':
	case 'S':
		translateCube(0.0, -0.1, 0.0);
		break;
	case 'w':
	case 'W':
		translateCube(0.0, 0.1, 0.0);
		break;
	case 'f':
	case 'F':
		scaleCube(0.9); 
		break;
	case 'r':
	case 'R':
		scaleCube(1.1);
		break;
	}
}

void display() {

	copyMatrix(vertices, altVertices);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	
	allAxisRotation(xAxisActivated, yAxisActivated, zAxisActivated, vertices, altVertices);

	cubeWireframe(altVertices);

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	cout << "X --> Rotacao eixo X\nY --> Rotacao eixo Y\nZ --> Rotacao eixo Z -->\n";
	cout << "A --> Deslocar para Esquerda\nD --> Deslocar para Direita\n";
	cout << "S --> Deslocar para Baixo\nW --> Deslocar para Cima\n";
	cout << "R --> Aumentar Escala\nF --> Reduzir Escala\n";

	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Cubo 3D");
	myInit();
	glutKeyboardFunc(keyboardControl);
	glutDisplayFunc(display);
	glutTimerFunc(16, update, 0);

	glutMainLoop();

	return 0;
}