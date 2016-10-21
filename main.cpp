#include "glsupport.h"
#include <GL/freeglut.h>

GLuint program;

GLuint vertexBufferVBO;
GLuint positionAttribute;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferVBO);
	
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(positionAttribute);

	glutSwapBuffers();
}

void init() {
	program = glCreateProgram();
	readAndCompileShader(program, "vertex.glsl", "fragment.glsl");

	glUseProgram(program);
	positionAttribute = glGetAttribLocation(program, "position");

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

	glewInit();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	init();
	glutMainLoop();
	return 0;
}