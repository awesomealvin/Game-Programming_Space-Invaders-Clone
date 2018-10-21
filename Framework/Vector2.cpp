#include "Vector2.h"

#include <cmath>


Vector2::Vector2() :
	m_x(0),
	m_y(0)
{
}


Vector2::~Vector2()
{
}

float Vector2::GetX() const
{
	return m_x;
}

float Vector2::GetY() const
{
	return m_y;
}

void Vector2::SetX(float x)
{
	m_x = x;
}

void Vector2::SetY(float y)
{
	m_y = y;
}

Vector2 Vector2::CalculateVectorFromAngle(float angle)
{
	Vector2 output;
	float radians = MyUtility::GetInstance().ToRadians(angle);
	float x = cos(radians);
	float y = sin(radians);

	output.SetX(x);
	output.SetY(y);

	return output;
}

Vector2 & Vector2::operator*=(const float value)
{
	this->m_x *= value;
	this->m_y *= value;

	return *this;
}

