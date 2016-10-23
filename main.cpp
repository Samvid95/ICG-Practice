#include "glsupport.h"
#include <GL/freeglut.h>
#include "matrix4.h"

GLuint program;

GLuint vertexBufferVBO;
GLuint textureBufferVBO;


GLuint positionAttribute;

GLuint modelViewMatrixUniformLocation;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferVBO);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);

	Matrix4 objectMatrix;
	objectMatrix = objectMatrix.makeXRotation(45 * (float)timeSinceStart/1000.0f);

	Matrix4 eyeMatrix;
	eyeMatrix = eyeMatrix.makeTranslation(Cvec3(-0.5, 0.0, 0.0));

	Matrix4 modelViewMatrix;
	modelViewMatrix = inv(eyeMatrix) * objectMatrix;

	GLfloat glMatrix[16];
	modelViewMatrix.writeToColumnMajorMatrix(glMatrix);
	glUniformMatrix4fv(modelViewMatrixUniformLocation, 1, false, glMatrix);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(positionAttribute);
	glutSwapBuffers();
}

void init() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	program = glCreateProgram();
	readAndCompileShader(program, "vertex.glsl", "fragment.glsl");

	
	glUseProgram(program);
	positionAttribute = glGetAttribLocation(program, "position");
	modelViewMatrixUniformLocation = glGetUniformLocation(program, "modelViewMatrix");
	

	glGenBuffers(1, &vertexBufferVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferVBO);

	GLfloat data[] = {
		-0.5f, -0.5f,
		0.5f, 0.5f,
		0.5f, -0.5f,

		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, 0.5f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	

	
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void idle(void) {
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("CS-6533");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	init();
	glutMainLoop();
	return 0;
}