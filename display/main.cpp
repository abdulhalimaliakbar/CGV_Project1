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
int selectedFeature = -1;
vector<int> featureList;

vector3 *ctrlpoint;
GLfloat *origin, **distances;

const float epsilon = 1e-6;
const float sig = 0.15;
const int N = 30;
float inv[N][N*2];
vector3 weight[N];

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

	// render features
	glPointSize(10.0);
	glColor3f(1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);
	glBegin(GL_POINTS);
	for (int i = 0; i < featureList.size(); i++)
	{
		int idx = featureList[i];

		glVertex3fv((float *)&mesh->vertices[3 * idx]);
	}
	glEnd();

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

GLfloat preventZero(GLfloat f)
{
	if (f == 0) {
		return epsilon;
	}
	return f;
}

void addControlPoint(int idx)
{
	printf("%d\n", idx);
	featureList.push_back(idx);

	ctrlpoint[idx] = vector3(
		preventZero(mesh->vertices[3 * idx + 0] - origin[3 * idx + 0]),
		preventZero(mesh->vertices[3 * idx + 1] - origin[3 * idx + 1]),
		preventZero(mesh->vertices[3 * idx + 2] - origin[3 * idx + 2]));
}

void mouse(int button, int state, int x, int y)
{
	tbMouse(button, state, x, y);

	// add feature
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
	{
		int minIdx = 0;
		float minDis = 9999999.0f;

		vector3 pos = Unprojection(vector2((float)x, (float)y));

		for (int i = 0; i < mesh->numvertices; i++)
		{
			vector3 pt(mesh->vertices[3 * i + 0], mesh->vertices[3 * i + 1], mesh->vertices[3 * i + 2]);
			float dis = (pos - pt).length();

			if (minDis > dis)
			{
				minDis = dis;
				minIdx = i;
			}
		}


		if (std::find(featureList.begin(), featureList.end(), minIdx) == featureList.end())
		{
			addControlPoint(minIdx);
		}

	}

	// manipulate feature
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		int minIdx = 0;
		float minDis = 9999999.0f;

		vector3 pos = Unprojection(vector2((float)x, (float)y));

		for (int i = 0; i < featureList.size(); i++)
		{
			int idx = featureList[i];
			vector3 pt(mesh->vertices[3 * idx + 0], mesh->vertices[3 * idx + 1], mesh->vertices[3 * idx + 2]);
			float dis = (pos - pt).length();

			if (minDis > dis)
			{
				minDis = dis;
				minIdx = featureList[i];
			}
		}

		selectedFeature = minIdx;

	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		selectedFeature = -1;

	last_x = x;
	last_y = y;
}

void calc_weight()
{
	// init
	for (int i = 0; i < featureList.size(); ++i)
	{
		inv[i][i] = 1;
		for (int j = i + 1; j < featureList.size(); ++j)
		{
			inv[j][i] = inv[i][j] = distances[featureList[i]][featureList[j]];
		}
		for (int j = 0; j < featureList.size(); ++j)
		{
			if (i == j)
			{
				inv[i][j+featureList.size()] = 1;
			}
			else
			{
				inv[i][j+featureList.size()] = 0;
			}
		}
	}


	// rref
	for (int i = 0; i < featureList.size(); ++i)
	{
		float pivot = inv[i][i];
		for (int j = i; j < 2 * featureList.size(); ++j)
		{
			inv[i][j] /= pivot;
		}
		for (int k = 0; k < featureList.size(); ++k)
		{
			if (i == k) { continue; }
			float factor = inv[k][i];
			for (int j = i; j < 2 * featureList.size(); ++j)
			{
				inv[k][j] -= inv[i][j] * factor;
			}
		}
	}

	for (int i = 0; i < featureList.size(); ++i)
	{
		int idx = featureList[i];
		vector3 vi = ctrlpoint[idx];
		vector3 wvi(0, 0, 0);
		for (int j = 0; j < featureList.size(); ++j)
		{
			int idx = featureList[j];
			wvi += inv[i][j + featureList.size()] * ctrlpoint[idx];
		}

		weight[i].x = wvi.x / vi.x;
		weight[i].y = wvi.y / vi.y;
		weight[i].z = wvi.z / vi.z;
	}
}

void move_together()
{
	calc_weight();
	memcpy(mesh->vertices, origin, sizeof(GLfloat) * mesh->numvertices * 3);
	for (int i = 0; i < featureList.size(); i++)
	{
		vector3 vec = ctrlpoint[featureList[i]];
		vec.x *= weight[i].x;
		vec.y *= weight[i].y;
		vec.z *= weight[i].z;
		for (int j = 0; j < mesh->numvertices; j++)
		{
			float dis = distances[featureList[i]][j];

			mesh->vertices[3 * j + 0] += dis * vec.x;
			mesh->vertices[3 * j + 1] += dis * vec.y;
			mesh->vertices[3 * j + 2] += dis * vec.z;
		}
	}
}

void motion(int x, int y)
{
	tbMotion(x, y);

	if (selectedFeature != -1)
	{
		matrix44 m;
		vector4 vec = vector4((float)(x - last_x) / 100.0f, (float)(y - last_y) / 100.0f, 0.0, 1.0);

		gettbMatrix((float *)&m);
		vec = m * vec;
		vec /= 2;

		ctrlpoint[selectedFeature].x += vec.x;
		ctrlpoint[selectedFeature].y -= vec.y;
		ctrlpoint[selectedFeature].z += vec.z;
	}

	move_together();
	last_x = x;
	last_y = y;
}

void timf(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, timf, 0);
}


int main(int argc, char *argv[])
{
	WindWidth = 400;
	WindHeight = 400;

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };

	glutInit(&argc, argv);
	glutInitWindowSize(WindWidth, WindHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Trackball Example");

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
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
	mesh = glmReadOBJ("./data/head.obj");

	glmUnitize(mesh);
	glmFacetNormals(mesh);
	glmVertexNormals(mesh, 90.0);

	ctrlpoint = (vector3*)malloc(sizeof(vector3)*mesh->numvertices);
	origin = (GLfloat*)malloc(sizeof(GLfloat) * mesh->numvertices * 3);
	memcpy(origin, mesh->vertices, sizeof(GLfloat) * mesh->numvertices * 3);

	distances = (GLfloat**)malloc(sizeof(GLfloat*) * mesh->numvertices);
	for (int i = 0; i < mesh->numvertices; i++)
	{
		distances[i] = (GLfloat*)malloc(sizeof(GLfloat) * mesh->numvertices);
	}
	for (int i = 0; i < mesh->numvertices; i++)
	{
		// prevent inf
		ctrlpoint[i] = vector3(0, 0, 0);

		vector3 pi(origin[3 * i + 0], origin[3 * i + 1], origin[3 * i + 2]);
		for (int j = 0; j < mesh->numvertices; j++)
		{
			vector3 pj(origin[3 * j + 0], origin[3 * j + 1], origin[3 * j + 2]);
			float dis = (pi - pj).length();
			distances[i][j] = distances[j][i] = exp(-dis*(dis / (2 * sig*sig)));
		}
	}

	addControlPoint(990);
	addControlPoint(2167);
	//addControlPoint(751);
	glutMainLoop();

	return 0;

}

