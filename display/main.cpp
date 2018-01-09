#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <numeric>
#include <iostream>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "glm.h"
#include "mtxlib.h"
#include "trackball.h"

using namespace std;

_GLMmodel *mesh;
int WindWidth, WindHeight;

int last_x, last_y;

const float epsilon = 1e-6;

void Reshape(int width, int height)
{
	int base = min(width, height);

	tbReshape(width, height);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLdouble)width / (GLdouble)height, 1.0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -3.5);

	WindWidth = width;
	WindHeight = height;
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	tbMatrix();

	// render solid model
	glEnable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glmDraw(mesh, GLM_SMOOTH);

	// render wire model
	glPolygonOffset(1.0, 1.0);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glLineWidth(1.0f);
	glColor3f(0.6, 0.0, 0.8);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glmDraw(mesh, GLM_SMOOTH);

	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

vector3 Unprojection(vector2 _2Dpos)
{
	float Depth;
	int viewport[4];
	double ModelViewMatrix[16];				//Model_view matrix
	double ProjectionMatrix[16];			//Projection matrix

	glPushMatrix();
	tbMatrix();

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMatrix);

	glPopMatrix();

	glReadPixels((int)_2Dpos.x, viewport[3] - (int)_2Dpos.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Depth);

	double X = _2Dpos.x;
	double Y = _2Dpos.y;
	double wpos[3] = { 0.0 , 0.0 , 0.0 };

	gluUnProject(X, ((double)viewport[3] - Y), (double)Depth, ModelViewMatrix, ProjectionMatrix, viewport, &wpos[0], &wpos[1], &wpos[2]);

	return vector3(wpos[0], wpos[1], wpos[2]);
}

void mouse(int button, int state, int x, int y)
{
	tbMouse(button, state, x, y);


	last_x = x;
	last_y = y;
}

void motion(int x, int y)
{
	tbMotion(x, y);
	last_x = x;
	last_y = y;
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 27: // ESC
		exit(0);
		break;
	}
}

void timf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, timf, 0);
}


int main(int argc, char *argv[])
{
	WindWidth = 1024;
	WindHeight = 768;

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

	glutInit(&argc, argv);
	glutInitWindowSize(WindWidth, WindHeight);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-WindWidth)/2,
                       (glutGet(GLUT_SCREEN_HEIGHT)-WindHeight)/2);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Display Animation");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(Keyboard);
	glClearColor(0, 0, 0, 0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	tbInit(GLUT_LEFT_BUTTON);
	tbAnimate(GL_FALSE);

	glutTimerFunc(40, timf, 0); // Set up timer for 40ms, about 25 fps

	// load 3D model
	std::cout << "Loading model ... ";
	mesh = glmReadOBJ("./data/head.obj");
	std::cout << "done." << std::endl;

	glmUnitize(mesh);
	glmFacetNormals(mesh);
	glmVertexNormals(mesh, 90.0);
	glutMainLoop();

	return 0;

}

