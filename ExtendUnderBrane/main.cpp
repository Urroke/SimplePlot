#include "pch.h"
#include "headers/Curve.h"
#include "headers/Scene.h"
#include "headers/Camera.h"
#include "headers/Cube.h"
#include "headers/TextureManager.h"

#define ESCAPE 27

const unsigned int amount_textures = 2;
unsigned int textures[amount_textures] = { 0, 1 };
//==========================================================================
// define global variable
Camera Camera::instance;
#define MainCamera Camera::getInstance()

Scene Scene::instance;
UserEventSystem UserEventSystem::instance;

// for window
int WIDTH = 1200, HEIGHT = 800;
bool fullscreen = false;
// speed of a camera
const float SPEED_MOVEMENT =  0.05f * 2;
const float SPEED_ROTATE =    0.005f * 2;

// for fps counter
int frames = 0;
unsigned long long curr_time = 0, timebase = 0, deltaTime = 0;
std::string str_fps;

//==========================================================================
// set of standart fonts
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
void print2dText(double x, double y, const char* str, std::string font = "ROMAN24")
{
	glRasterPos2d(x, y);
	std::for_each(font.begin(), font.end(), [](char& c) {
		c = ::toupper(c);
		});
	glutBitmapString(fontMap[font], reinterpret_cast<const unsigned char*>(str));
}

//==========================================================================
void print3dText(double x, double y, double z, const char* str, std::string font = "ROMAN24")
{
	glRasterPos3d(x, y, z);
	std::for_each(font.begin(), font.end(), [](char& c) {
		c = ::toupper(c);
		});
	glutBitmapString(fontMap[font], reinterpret_cast<const unsigned char*>(str));
}

//==========================================================================
void drawAxis()
{
	glDisable(GL_DEPTH_TEST);

	// draw axis
	glLineWidth(3);
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(5, 0, 0); // x

		glColor3f(0, 1, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 5, 0);  // y

		glColor3f(0, 0, 1);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 5);  // z
	glEnd();

	// draw direction triangles
	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);
		glVertex3i(5, 0, 0);		// x
		glVertex3f(4.5f, 0, -0.15f);
		glVertex3f(4.5f, 0, 0.15f);
		
		glColor3f(0, 1, 0);
		glVertex3i(0, 5, 0);		// y
		glVertex3f(0.15f, 4.5f, 0);
		glVertex3f(-0.15f, 4.5f, 0);
		
		glColor3f(0, 0, 1);
		glVertex3i(0, 0, 5);		// z
		glVertex3f(0.15f, 0, 4.5f);
		glVertex3f(-0.15f, 0, 4.5f);
	glEnd();

	// name of direction (axis)255, 135, 50
	glColor3f(0.01, 0.01, 1);
	print3dText(5, 0, 0.2, "X");
	print3dText(0.2, 5, 0, "Y");
	print3dText(0.2, 0, 5, "Z");

	glEnable(GL_DEPTH_TEST);
}

//==========================================================================
void fpsPrint()
{
	glDisable(GL_DEPTH_TEST);
	glColor3f(0.0f, 0.6f, 0.0f);
	print2dText(0, 0, str_fps.c_str());
	glEnable(GL_DEPTH_TEST);
}

//==========================================================================
std::string fps_counter()
{
	str_fps.clear();
	float framesPerSecond = 1000.0f / float(frames);
	int fps = frames;
	str_fps += "fps: " + std::to_string(fps);
	timebase = curr_time;
	frames = 0;
	printf("%s, frames per second(ms) %f, deltaTime:%lli\n", str_fps.c_str(), framesPerSecond, deltaTime);
	return str_fps;
}

//==========================================================================
constexpr float step = 9.0f / 255.0f;
void display() {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	frames++;
	curr_time = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = curr_time - timebase;
	if (deltaTime >= 1000)
		str_fps = fps_counter();

	// Reset transformations
	glLoadIdentity();

	MainCamera.update();
	Scene::getInstance().render();

	glEnable(GL_TEXTURE_2D);
	TextureManager::Inst()->BindTexture(textures[0]);
	// Draw ground
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);			//plane
		glTexCoord2i(0, 0); glVertex3f(-100.0f, 0.0f, -100.0f);
		glTexCoord2i(0, 1); glVertex3f(-100.0f, 0.0f, 100.0f);
		glTexCoord2i(1, 1); glVertex3f(100.0f, 0.0f, 100.0f);
		glTexCoord2i(1, 0); glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	for (float red = 0; red < 1; red += step)
	{
		for (float green = 0; green < 1; green += step)
		{
			for (float blue = 0; blue < 1; blue += step)
			{
				glPointSize(6);
				glBegin(GL_POINTS);
					glColor3f(red, green, blue);
					glVertex3f(red * 20.0f, green * 20.0f + 10, blue * 20.0f);
				glEnd();
			}
		}
	}

	// yellow sphere
	glPushMatrix();
		GLUquadricObj* quadObj = gluNewQuadric();
		glColor3f(1.f, 1.f, 0.f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		GLfloat color[] = { 1,1,1,0 };
		glMaterialfv(GL_LIGHT0, GL_POSITION, color);
		glTranslatef(10.0f, 60.0f, 10.0f);
		gluSphere(quadObj, 10, 100, 100); 
	glPopMatrix();
	gluDeleteQuadric(quadObj);

	drawAxis();
	fpsPrint();

	glutSwapBuffers();
}

//==========================================================================
void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	UserEventSystem::initialize();

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

//==========================================================================
int main(int argc, char** argv) {
	float speed = SPEED_MOVEMENT;
	float angleSpeed = SPEED_ROTATE;
	bool movex = false, movex_ = false, movez = false, movez_ = false;
	bool moveup = false, movedown = false, moveright = false, moveleft = false;

	float pos[4] = { 10.0f, 10.0f, 10.0f, 1.f };		// ��� ��������� �����������
	float dir[3] = { 0.f, -1.f, 0.f };	// �����������, ���� ������� ��� ��������

	TextureManager::Inst()->LoadTexture("../../textures/snow.jpeg", textures[0]);

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

	MainCamera.tfm.position = Point3d(5, 10, -50);

	// init GLUT and create window
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

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	// ��������� (���� ���������� � ��� ����� ��������� ���������)
	//glLightfv(GL_LIGHT0, GL_POSITION, pos);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	std::function<void(unsigned char, int, int)> key_press = [&](unsigned char key, int x, int y)
	{
		printf("%c, %d, %d\n", key, x, y);
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
		if (key == ESCAPE)
			exit(0);
	};
	UserEventSystem::getInstance().onKeyPress.subscribe(key_press);

	std::function<void(unsigned char, int, int)> key_up = [&](unsigned char key, int x, int y)
	{
		printf("%c, %d, %d\n", key, x, y);
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
		if (key == ESCAPE)
			exit(0);
	};
	UserEventSystem::getInstance().onKeyUp.subscribe(key_up);

	std::function<void(MouseWheelDirection,int,int)> mouse_wheel = [](MouseWheelDirection dir, int x, int y)
	{
		printf("%s, %d, %d\n", dir == MouseWheelDirection::UP ? "UP" : "DOWN", x, y);
	};
	UserEventSystem::getInstance().onMouseWheel.subscribe(mouse_wheel);
	
	std::function<void( int, int)> mouse_move = [](int x, int y)
	{
		printf("%d %d\n", x,y);
	};
	UserEventSystem::getInstance().onMouseMove.subscribe(mouse_move);
	
	glutMainLoop();

	TextureManager::Inst()->UnloadAllTextures();
	return 1;
}
