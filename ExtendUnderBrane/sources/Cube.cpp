#include "../headers/Cube.h"

void Cube::render() const
{

	const double size = 100;
	glPointSize(1.);
	glEnable(GL_POINT_SMOOTH);
	glColor3d(1, 0, 0);
	double x_p, y_p;
	glBegin(GL_QUADS);
	glEnable(GL_DEPTH_TEST);
	auto position = transform.position;
	glutWireCube(size);
	
		
	glEnd();
	
}
