#include <GL/glut.h>
#include <cmath>
#include "Interval.h"
#include "Curve.h"
#include "Scene.h"
#include <iostream>

Scene mainScene;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	mainScene.render();
	//drawCircle(100);
	glFlush();
}
void Initialize() {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}
int main(int argc, char ** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Our first GLUT application!");
	
	double angle = 0;
	Curve one([](double x)->double {return x * x; }, { -1, 1 });
	Curve two([](double x)->double {return std::sin(x); }, { -2, 2 });
	mainScene += one;
	mainScene += two;

	std::function<void(void)> kadr = [&]()->void
	{
		angle+=0.01;
		one.transform.setRotation(angle, Vector3d(1, 0, 0));
		two.transform.setRotation(angle, Vector3d(0, 1, 0));
		std::cout << "LEL\n";
	};

	mainScene.subscribeCallBack(kadr);

	
	
	
	

	glutDisplayFunc(display);
	glutIdleFunc(display);
	Initialize();
	
	
	glutMainLoop();
	return 0;
}