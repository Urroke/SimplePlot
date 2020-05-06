#include "pch.h"
#include "Curve.h"
#include "Scene.h"
#include "Camera.h"
#include "Cube.h"

//==========================================================================
Camera Camera::instance;
#define MainCamera Camera::getInstance()

Scene Scene::instance;
UserEventSystem UserEventSystem::instance;

int WIDTH = 1200, HEIGHT = 800;
bool fullscreen = false;

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

//==========================================================================
void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

//==========================================================================
void display() {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	MainCamera.update();
	Scene::getInstance().render();

	// Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);			//plane
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}

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
void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	double speed = 0.1;
	double angleSpeed = 0.005;
	bool movex = false, movex_ = false, movez = false, movez_ = false;
	bool moveup = false, movedown = false, moveright = false, moveleft = false;
	Scene::getInstance().subscribeCallBack([&]() -> void {
		if (movez)
			MainCamera.tfm.position += MainCamera.tfm.rotation * Vector3d(0, 0, speed);
		if (movex_)
			MainCamera.tfm.position += MainCamera.tfm.rotation * Vector3d(speed, 0, 0.0);
		if (movez_)
			MainCamera.tfm.position += MainCamera.tfm.rotation * Vector3d(0, 0, -speed);
		if (movex)
			MainCamera.tfm.position += MainCamera.tfm.rotation * Vector3d(-speed, 0, 0.0);
		if (moveleft)
			MainCamera.tfm.rotateBy(angleSpeed, Vector3d(0, 1, 0));
		if (moveright)
			MainCamera.tfm.rotateBy(-angleSpeed, Vector3d(0, 1, 0));
		if (moveup)
			MainCamera.tfm.rotateBy(angleSpeed, Vector3d(1, 0, 0));
		if (movedown)
			MainCamera.tfm.rotateBy(-angleSpeed, Vector3d(1, 0, 0));
		});

	UserEventSystem::getInstance().onKeyUp.subscribe([&](unsigned char key, int x, int y) -> void {
		if (key == 'w')
			movez = false;
		if (key == 'a')
			movex_ = false;
		if (key == 's')
			movez_ = false;
		if (key == 'd')
			movex = false;
		if (key == 'q')
			moveleft = false;
		if (key == 'e')
			moveright = false;
		if (key == 'r')
			moveup = false;
		if (key == 'f')
			movedown = false;
		if (key == 27)
			exit(0);
		});

	UserEventSystem::getInstance().onKeyPress.subscribe([&](unsigned char key, int x, int y) -> void {
		if (key == 'w')
			movez = true;
		if (key == 'a')
			movex_ = true;
		if (key == 's')
			movez_ = true;
		if (key == 'd')
			movex = true;
		if (key == 'q')
			moveleft = true;
		if (key == 'e')
			moveright = true;
		if (key == 'r')
			moveup = true;
		if (key == 'f')
			movedown = true;
		if (key == 27)
			exit(0);
		});
	
	// init GLUT and create window
	MainCamera.tfm.position = Point3d(0, 1, 2);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 20);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("SimplePlot");

	if(fullscreen)
		glutFullScreen();

	// register callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(changeSize);
	glutIdleFunc(display);

	glutKeyboardFunc([](unsigned char c, int x, int y) {
		UserEventSystem::getInstance().keyboard_event(c, x, y);
		});

	glutKeyboardUpFunc([](unsigned char c, int x, int y) {
		UserEventSystem::getInstance().keyboard_event_up(c, x, y);
		});

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

//==========================================================================
/*int main(int argc, char ** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 20);
	glutCreateWindow("SimplePlot");

	int frame = 0, fps = 0;
	unsigned long long time = 0, timebase = 0;
	std::string str_fps;

	double angle = 0;
	Curve one([](double x)->double {return x * x; }, { -2, 2 });
	Curve two([](double x)->double {return std::sin(x); }, { -2, 2 });
	Cube cube;
	Scene::getInstance() += one;
	Scene::getInstance() += cube;
	Scene::getInstance() += two;


	std::function<void(void)> eachFrame = [&]()->void
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

		angle += 0.1;
		one.transform.setRotation(angle, Vector3d(1, 0, 0));
		two.transform.setRotation(angle, Vector3d(0, 1, 0));
		cube.transform.setRotation(angle, Vector3d(0, 1, 0));

		// по топу: хер знает как поместить автоматически в край угла, он сдвигает его после изменения glOrtho констант
		printText(glOleft, glOtop - 2, 0, str_fps.c_str(), "roman24");	
	};

	Scene::getInstance().subscribeCallBack(eachFrame);
	std::function<void(MouseWheelDirection,int,int)> func = [](MouseWheelDirection dir, int x, int y)
	{	
		printf("%s, %d, %d\n", dir == MouseWheelDirection::UP ? "UP" : "DOWN", x, y);
	};
	
	UserEventSystem::getInstance().onMouseWheel.subscribe(func);
	
	glutDisplayFunc(display);
	glutMouseWheelFunc([](int button, int dir, int x, int y)
		{
			UserEventSystem::getInstance().mousewhell_event(button, dir, x, y);
		});
	glutKeyboardFunc([](unsigned char c, int x, int y)
		{
			UserEventSystem::getInstance().keyboard_event(c, x, y);
		});
	glutIdleFunc(display);
	Initialize();

	glutMainLoop();
	return 0;
}*/
