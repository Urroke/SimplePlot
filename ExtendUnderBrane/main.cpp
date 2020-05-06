#include "pch.h"
#include "Curve.h"
#include "Scene.h"
#include "Camera.h"

//==========================================================================
Scene mainScene;
constexpr int WIDTH = 800, HEIGHT = 600;
bool full_screen = false;
int limit_frames = 60;

// for glOrtho
constexpr double glOleft = -10, glOright = 10;
constexpr double glObottom = -10, glOtop = 10;
constexpr double glOzNear = -10, glOzFar = 10;

//==========================================================================
static std::map<std::string, void*> fontMap = {
	{ "8BY13" , GLUT_BITMAP_8_BY_13},
	{ "9BY15" , GLUT_BITMAP_9_BY_15},
	{ "ROMAN10" , GLUT_BITMAP_TIMES_ROMAN_10},
	{ "ROMAN24" , GLUT_BITMAP_TIMES_ROMAN_24},
	{ "HELVETICA10" , GLUT_BITMAP_HELVETICA_10},
	{ "HELVETICA12" , GLUT_BITMAP_HELVETICA_12},
	{ "HELVETICA18" , GLUT_BITMAP_HELVETICA_18},
};

/*
//==========================================================================
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
}*/

//==========================================================================
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); // red
	mainScene.render();
	glFlush();
	glutSwapBuffers();
}

//==========================================================================
void printText(double x, double y, double z, const char* str, std::string font = "8BY13")
{
	glRasterPos3d(x, y, z);
	std::for_each(font.begin(), font.end(), [](char& c) {
		c = ::toupper(c);
	});
	glutBitmapString(fontMap[font], reinterpret_cast<const unsigned char*>(str));
}

//==========================================================================
void Initialize() {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(glOleft, glOright, glObottom, glOtop, glOzNear, glOzFar);
}

//==========================================================================
int main(int argc, char ** argv) {
	int frame = 0, fps = 0;
	unsigned long long time = 0, timebase = 0;
	std::string str_fps;

	double angle = 0;
	Curve one([](double x)->double {return x * x; }, { -2, 2 });
	Curve two([](double x)->double {return std::sin(x); }, { -2, 2 });
	mainScene += one;
	mainScene += two;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 20);
	glutCreateWindow("SimplePlot");

	std::function<void(void)> kadr = [&]()->void
	{
		frame++;
		time = glutGet(GLUT_ELAPSED_TIME);
		if (time - timebase > 1000) {
			str_fps.clear();
			fps = frame * 1000.0 / double(time - timebase);
			str_fps += "fps: " + std::to_string(fps);
			timebase = time;
			frame = 0;
		}

		angle += 0.01;
		one.transform.setRotation(angle, Vector3d(1, 0, 0));
		two.transform.setRotation(angle, Vector3d(0, 1, 0));
		// по топу: хер знает как поместить автоматически в край угла, он сдвигает его после изменения glOrtho констант
		printText(glOleft, glOtop - 2, 0, str_fps.c_str(), "roman24");	
	};

	mainScene.subscribeCallBack(kadr);

	glutDisplayFunc(display);
	glutIdleFunc(display);
	Initialize();

	glutMainLoop();
	return 0;
}
