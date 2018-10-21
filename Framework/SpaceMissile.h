#pragma once
#include "entity.h"
#include "Vector2.h"
class SpaceMissile :
	public Entity
{
public:
	SpaceMissile();
	~SpaceMissile();

	void SetTarget(float x, float y);

	void Process(float deltaTime);

private:
	Vector2 m_target;

	const float TIME_TO_HIT;
	
};

