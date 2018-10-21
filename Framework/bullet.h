#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	~Bullet();

	void Process(float deltaTime);

	bool CanTrail() const;
	void SetTrail(bool v);

private:
	float m_elapsedTime;
	const float MIN_TRAIL_SPAWN_TIME;
	const float MAX_TRAIL_SPAWN_TIME;
	float m_trailSpawnTime;

	bool m_canTrail;
};

#endif