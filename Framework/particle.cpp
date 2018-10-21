#include "particle.h"
#include "MyUtility.h"

Particle::Particle() :
	m_spriteAngle(0.0f)
{
}

bool Particle::Initialise(Sprite * sprite)
{
	Entity::Initialise(sprite);

	return true;
}

void Particle::Revive(float x, float y)
{
	m_dead = false;
	m_currentAliveTime = 0;

	m_aliveTime = MyUtility::GetInstance().RandomFloat(m_minAliveTime, m_maxAliveTime);

	m_x = x - (GetSpriteWidth()/2);
	m_y = y - (GetSpriteHeight()/2);
}

void Particle::Process(float deltaTime)
{
	Entity::Process(deltaTime);

	m_currentAliveTime += deltaTime;
	if (m_currentAliveTime >= m_aliveTime)
	{
		SetDead(true);
	}
}

void Particle::DrawRotation(BackBuffer & backBuffer)
{
	Entity::DrawRotation(backBuffer, m_spriteAngle);
}
