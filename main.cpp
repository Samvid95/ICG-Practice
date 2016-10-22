#include "glsupport.h"
#include <GL/freeglut.h>

GLuint program;

GLuint vertexBufferVBO;
GLuint textureBufferVBO;


GLuint positionAttribute;
GLuint texCoordAttribute;

GLuint smurf;

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferVBO);
	glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, FALSE, 0, 0);
	glEnableVertexAttribArray(positionAttribute);

	
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferVBO);
	glVertexAttribPointer(texCoordAttribute, 2, GL_FLOAT, FALSE, 0, 0);
	glEnableVertexAttribArray(texCoordAttribute);

	glBindTexture(GL_TEXTURE_2D, smurf);
	

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(positionAttribute);
	glDisableVertexAttribArray(texCoordAttribute);

	glutSwapBuffers();
}

void init() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	program = glCreateProgram();
	readAndCompileShader(program, "vertex.glsl", "fragment.glsl");

	smurf = loadGLTexture("Smurf1.png");
	glUseProgram(program);
	positionAttribute = glGetAttribLocation(program, "position");
	texCoordAttribute = glGetAttribLocation(program, "texCoord");

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
	
	glGenBuffers(1, &textureBufferVBO);
	glBindBuffer(GL_ARRAY_BUFFER, textureBufferVBO);

	GLfloat textureData[] = {
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(textureData), textureData, GL_STATIC_DRAW);
	
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