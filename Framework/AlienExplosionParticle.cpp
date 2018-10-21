#include "AlienExplosionParticle.h"
#include "MyUtility.h"


AlienExplosionParticle::AlienExplosionParticle() 
{
	m_minAliveTime = 0.50f;
	m_maxAliveTime = 0.75f;
}


AlienExplosionParticle::~AlienExplosionParticle()
{

}

void AlienExplosionParticle::Revive(float x, float y)
{
	Particle::Revive(x, y);
	//m_maxAliveTime = MyUtility::GetInstance().RandomFloat(MIN_ALIVE_TIME, MAX_ALIVE_TIME);
	m_spriteAngle = MyUtility::GetInstance().RandomFloat(0, 360);
}

