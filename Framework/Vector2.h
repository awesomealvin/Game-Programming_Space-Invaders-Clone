#pragma once
#include "MyUtility.h"

class Vector2
{
public:
	Vector2();
	~Vector2();

	float GetX() const;
	float GetY() const;

	void SetX(float x);
	void SetY(float y);

	static Vector2 CalculateVectorFromAngle(float angle);

	Vector2& operator*=(const float value);

private:
	float m_x;
	float m_y;
};

