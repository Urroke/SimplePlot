#include "pch.h"
#include "Curve.h"
#include "Scene.h"
#include "Camera.h"
  /* function declarations */

//==========================================================================
Scene mainScene;
int width = 1200, height = 800;

//==========================================================================
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	mainScene.render(); 
	glFlush();
}

/*static std::map
{
	GLUT_BITMAP_8_BY_13
	GLUT_BITMAP_9_BY_15
	GLUT_BITMAP_TIMES_ROMAN_10
	GLUT_BITMAP_TIMES_ROMAN_24
	GLUT_BITMAP_HELVETICA_10
	GLUT_BITMAP_HELVETICA_12
	GLUT_BITMAP_HELVETICA_18
};*/

void printText(double x, double y, double z, const unsigned char* str, void* font = GLUT_BITMAP_TIMES_ROMAN_10)
{
	glRasterPos3d(x, y, z);
	glutBitmapString(font, str);
}

//==========================================================================
void Initialize() {
	glClearColor(0.8, 1.0, 0.6, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 5.0);
}

//==========================================================================
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
		//std::cout << "LEL\n";
	};

	mainScene.subscribeCallBack(kadr);
	
	//printText(10, 10, 10, )
	//glutStrokeCharacter();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	Initialize();
	

	glutMainLoop();
	return 0;
}
