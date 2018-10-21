#pragma once
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "entity.h"

class Particle : public Entity {
public:
	Particle();

	 bool Initialise(Sprite* sprite);

	 void Revive(float x, float y);
	 void Process(float deltaTime);
	 void DrawRotation(BackBuffer& backBuffer);

protected:

	float m_minAliveTime;
	float m_maxAliveTime;
	float m_currentAliveTime;
	float m_aliveTime;

	float m_spriteAngle;
};

#endif // __PARTICLE_H__