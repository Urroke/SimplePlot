#include "cmath"
#include "../headers/Transform.h"

Transform::Transform()
{
	position = Point3d(0, 0, 0);
	setRotation(0, Vector3d(0, 0, 1));
	scale = 1.;
}

Vector3d operator*(const Matrix& matrix, const Vector3d& vec)
{
	Vector3d res;
	res.x = matrix[0][0] * vec.x + matrix[0][1] * vec.y + matrix[0][2] * vec.z;
	res.y = matrix[1][0] * vec.x + matrix[1][1] * vec.y + matrix[1][2] * vec.z;
	res.z = matrix[2][0] * vec.x + matrix[2][1] * vec.y + matrix[2][2] * vec.z;
	return res;
}

Matrix operator*(const Matrix& mat1, const Matrix& mat2)
{
	Matrix res;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j)
		{
			res[i][j] = 0;
			for (int k = 0; k < 3; ++k)
			{
				res[i][j] += mat1[i][k] * mat2[k][j];
			}
		}
	}
	return res;
}

Point3d operator*(const Matrix& matrix, const Point3d& point)
{
	Point3d res;
	res.x = matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2] * point.z;
	res.y = matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2] * point.z;
	res.z = matrix[2][0] * point.x + matrix[2][1] * point.y + matrix[2][2] * point.z;
	return res;
}

Transform::Transform(const Point3d& position, const Matrix& rotation, double scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}

void Transform::setScale(double scale)
{
	this->scale = scale;
}

void Transform::scaleTo(double mult)
{
	scale *= mult;
}

void Transform::translateTo(const Vector3d& vec)
{
	position += vec;
}

void Transform::setPosition(const Point3d& position)
{
	this->position = position;
}

void Transform::moveUp(double y)
{
	this->position.y += y;
}

void Transform::moveDown(double y)
{
	this->position.y -= y;
}

void Transform::setRotation(double a, const Vector3d& vec)
{
	Vector3d d = vec.normal();
	double cosa = std::cos(a);
	double cosa1 = 1 - cosa;
	double sina = std::sin(a);
	rotation[0][0] = cosa + d.x * d.x * cosa1;
	rotation[0][1] = d.x * d.y * cosa1 - d.z * sina;
	rotation[0][2] = d.x * d.z * cosa1 + d.y * sina;
	rotation[1][0] = d.x * d.y * cosa1 + d.z * sina;
	rotation[1][1] = cosa + d.y * d.y * cosa1;
	rotation[1][2] = d.y * d.z * cosa1 - d.x * sina;
	rotation[2][0] = d.x * d.z * cosa1 - d.y * sina;
	rotation[2][1] = d.y * d.z * cosa1 + d.x * sina;
	rotation[2][2] = cosa + d.z * d.z * cosa1;
}

void Transform::rotateBy(double a, const Vector3d& vec)
{
	Matrix rotate = getRotation(a, vec);
	rotation = rotation * rotate;
}

// x axis
void Transform::rotatePitch(double angle)
{
	Matrix rotate = getRotation(angle, Vector3d(1, 0, 0));
	rotate[0][0] = 1;
	rotate[0][1] = 0;
	rotate[0][2] = 0;

	rotate[1][0] = 0;
	rotate[1][1] = cos(angle);
	rotate[1][2] = -sin(angle);
	
	rotate[2][0] = 0;
	rotate[2][1] = sin(angle);
	rotate[2][2] = cos(angle);
	rotation = rotate * rotation;
}

// y axis
void Transform::rotateYaw(double angle)
{
	//Matrix rotate = getRotation(angle, Vector3d(0, 1, 0));
	Matrix rotate;
	rotate[0][0] = cos(angle);
	rotate[0][1] = 0;
	rotate[0][2] = sin(angle);

	rotate[1][0] = 0;
	rotate[1][1] = 1;
	rotate[1][2] = 0;

	rotate[2][0] = -sin(angle);
	rotate[2][1] = 0;
	rotate[2][2] = cos(angle);
	rotation = rotation * rotate;
}

// z axis
void Transform::rotateRoll(double angle)	
{
	Matrix rotate = getRotation(angle, Vector3d(0, 0, 1));
	rotate[0][0] = cos(angle);
	rotate[0][1] = -sin(angle);
	rotate[0][2] = 0;

	rotate[1][0] = sin(angle);
	rotate[1][1] = cos(angle);
	rotate[1][2] = 0;

	rotate[2][0] = 0;
	rotate[2][1] = 0;
	rotate[2][2] = 1;
	rotation = rotation * rotate;
}

Matrix Transform::getRotation(double a, const Vector3d& vec)
{
	Vector3d d = vec.normal();
	double cosa = std::cos(a);
	double cosa1 = 1 - cosa;
	double sina = std::sin(a);
	Matrix rotate;
	rotate[0][0] = cosa + d.x * d.x * cosa1;
	rotate[0][1] = d.x * d.y * cosa1 - d.z * sina;
	rotate[0][2] = d.x * d.z * cosa1 + d.y * sina;
	rotate[1][0] = d.x * d.y * cosa1 + d.z * sina;
	rotate[1][1] = cosa + d.y * d.y * cosa1;
	rotate[1][2] = d.y * d.z * cosa1 - d.x * sina;
	rotate[2][0] = d.x * d.z * cosa1 - d.y * sina;
	rotate[2][1] = d.y * d.z * cosa1 + d.x * sina;;
	rotate[2][2] = cosa + d.z * d.z * cosa1;
	return rotate;
}
