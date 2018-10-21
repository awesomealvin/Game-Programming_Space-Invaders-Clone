#pragma once
#include "particle.h"
class AlienExplosionParticle :
	public Particle
{
public:
	AlienExplosionParticle();
	~AlienExplosionParticle();

	void Revive(float x, float y);

private:
	
};

