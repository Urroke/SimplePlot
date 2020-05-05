#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Curve.h"
#include "Scene.h"
#include <GL/glut.h>
#include "Camera.h"
#include "UserEventSystem.h"
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "GL/freeglut_std.h"
  /* function declarations */

int width = 1200, height = 800;

void
drawScene(void), setMatrix(void), initLightAndMaterial(void),
animation(void), resize(int w, int h), menu(int choice), keyboard(unsigned char c, int x, int y);

/* global variables */

float ax, ay, az;       /* angles for animation */
GLUquadricObj *quadObj; /* used in drawscene */
static float lmodel_twoside[] =
{ GL_TRUE };
static float lmodel_oneside[] =
{ GL_FALSE };

 Camera* Camera::instance;
 UserEventSystem* UserEventSystem::instance;

void mouse(int button, int state, int x, int y)
{
	printf("Scroll At %d %d\n", button, state);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	quadObj = gluNewQuadric();  /* this will be used in drawScene
								 */
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1200, 1200);
	glutCreateWindow("Two-sided lighting");

	ax = 10.0;
	ay = -10.0;
	az = 0.0;

	initLightAndMaterial();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutCreateMenu(menu);
	glutAddMenuEntry("Motion", 3);
	glutAddMenuEntry("Two-sided lighting", 1);
	glutAddMenuEntry("One-sided lighting", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc([](unsigned char c, int x, int y){
		UserEventSystem::getInstance().keyboard_event(c, x, y);
		});
	glutMouseWheelFunc([](int btn, int dir, int x, int y) {
		UserEventSystem::getInstance().mousewhell_event(btn, dir, x, y);
		});

	//glOrtho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
	//gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	//glm::mat4 proj = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);

	glutMainLoop();
	Curve one([](double x)->double {return x * x; }, { -1, 1 });
	Scene mainScene;
	mainScene += one;
	mainScene.render();
	glutDisplayFunc(drawScene);
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}

void drawScene(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(ax, 1.0, 0.0, 0.0);
	glRotatef(-ay, 0.0, 1.0, 0.0);

	gluCylinder(quadObj, 2.0, 5.0, 100.0, 20, 8);  /* draw a cone */
	gluSphere(quadObj, 10, 36, 18);
	glPopMatrix();

	glutSwapBuffers();
}

void setMatrix(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int count = 0;

void animation(void)
{
	ax += 5.0;
	ay -= 2.0;
	az += 5.0;
	if (ax >= 360)
		ax = 0.0;
	if (ay <= -360)
		ay = 0.0;
	if (az >= 360)
		az = 0.0;
	drawScene();
	count++;
	if (count >= 60)
		glutIdleFunc(NULL);
}



void menu(int choice)
{
	switch (choice) {
	case 3:
		count = 0;
		glutIdleFunc(animation);
		break;
	case 2:
		glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_oneside);
		glutSetWindowTitle("One-sided lighting");
		glutPostRedisplay();
		break;
	case 1:
		glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
		glutSetWindowTitle("Two-sided lighting");
		glutPostRedisplay();
		break;
	}
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	setMatrix();
}

void initLightAndMaterial(void)
{
	static float ambient[] =
	{ 0.1, 0.1, 0.1, 1.0 };
	static float diffuse[] =
	{ 0.5, 1.0, 1.0, 1.0 };
	static float position[] =
	{ 90.0, 90.0, 150.0, 0.0 };

	static float front_mat_shininess[] =
	{ 60.0 };
	static float front_mat_specular[] =
	{ 0.2, 0.2, 0.2, 1.0 };
	static float front_mat_diffuse[] =
	{ 0.5, 0.5, 0.28, 1.0 };
	static float back_mat_shininess[] =
	{ 60.0 };
	static float back_mat_specular[] =
	{ 0.5, 0.5, 0.2, 1.0 };
	static float back_mat_diffuse[] =
	{ 1.0, 0.9, 0.2, 1.0 };

	static float lmodel_ambient[] =
	{ 1.0, 1.0, 1.0, 1.0 };

	setMatrix();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT, GL_SHININESS, front_mat_shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR, front_mat_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, front_mat_diffuse);
	glMaterialfv(GL_BACK, GL_SHININESS, back_mat_shininess);
	glMaterialfv(GL_BACK, GL_SPECULAR, back_mat_specular);
	glMaterialfv(GL_BACK, GL_DIFFUSE, back_mat_diffuse);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
}