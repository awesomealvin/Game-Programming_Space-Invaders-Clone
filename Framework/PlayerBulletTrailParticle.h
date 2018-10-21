#pragma once
#include "particle.h"
class PlayerBulletTrailParticle :
	public Particle
{
public:
	PlayerBulletTrailParticle();
	~PlayerBulletTrailParticle();

	void Revive(float x, float y);


private:
	float const MIN_ANGLE;
	float const MAX_ANGLE;
	float m_angleVelocity;
};

