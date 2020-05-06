#include <GL/glut.h>
#include <cmath>
#include "Interval.h"
#include "Curve.h"
#include "Scene.h"
#include <iostream>
#include <chrono>
#include "CollisionSystem.h"
#include "Circle.h"
double deltaTime = 1;
Scene mainScene;

void display() {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	mainScene.render();
	//drawCircle(100);
	glFlush();
	end = std::chrono::system_clock::now();
	deltaTime = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count())/1000000000.;
}
void Initialize() {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

const double PI = 3.141592653589;

int sign(double x)
{
	return x > 0 ? x : -x;
}

int main(int argc, char ** argv) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 200);
	glutCreateWindow("Our first GLUT application!");
	
	double angle = 0;
	Curve one([](double x)->double {return x * x; }, { -PI, PI});
	Curve two([](double x)->double {return std::sqrt(1 - x*x); }, { -1, 1 });
	//mainScene += one;
	two.transform.translateTo(Vector3d(-5, 2, 0));
	mainScene += two;
	two.transform.scaleTo(0.5);

	double time = 0.;
	Vector3d velocity(0.04, 0.2, 0);
	double a = 0.1;
	Circle arr[100];
	CollisionSystem sys;
	for (int i = 0; i < 100; i++)
	{
		sys += arr[i];
		
		mainScene += arr[i];
		arr[i].transform.position = Point3d(double(rand() % 1000) / 50  -10, double(rand() % 1000) / 50 - 10, 0);
		arr[i].velocity = Vector3d(double(rand() % 1000) / 2000, double(rand() % 1000) / 2000, 0);
	}

	std::function<void(void)> kadr = [&]()->void
	{
		for (int i = 0; i < 100; i++) {
			arr[i].transform.position += arr[i].velocity*deltaTime*10;
			std::cout << arr[i].transform.position.y << "\n";
			if (arr[i].transform.position.y < -10)
			{
				arr[i].velocity.y *= -1.;
			}
			if (arr[i].transform.position.y > 10)
			{
				arr[i].velocity.y *= -1.;
			}
			if (arr[i].transform.position.x < -10)
			{
				arr[i].velocity.x *= -1.;
			}
			if (arr[i].transform.position.x > 10)
			{
				arr[i].velocity.x *= -1.;
			}
		}
		time += 0.0000002;
		sys.collision();
		//angle+=0.01;
		velocity += Vector3d(0, -a*deltaTime, 0);
		two.transform.position += velocity;
		if (two.transform.position.y < -10)
		{
			velocity.y *= -1.;
		}
		if (two.transform.position.y > 10)
		{
			velocity.y *= -1.;
		}
		if (two.transform.position.x < -10)
		{
			velocity.x *= -1.;
		}
		if (two.transform.position.x > 10)
		{
			velocity.x *= -1.;
		}
		two.transform.setRotation(angle, Vector3d(0, 1, 0));
	};

	mainScene.subscribeCallBack(kadr);

	
	
	
	

	glutDisplayFunc(display);
	glutIdleFunc(display);
	Initialize();
	
	
	glutMainLoop();
	return 0;
}