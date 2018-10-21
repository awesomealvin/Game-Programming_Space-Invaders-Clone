#include "bullet.h"
#include "MyUtility.h"

Bullet::Bullet() : 
	MIN_TRAIL_SPAWN_TIME(0.05f),
	MAX_TRAIL_SPAWN_TIME(0.075f)
{
	Entity::Entity();
	m_elapsedTime = 0;
	m_velocityX = 0;
	m_trailSpawnTime = MyUtility::GetInstance().RandomFloat(MIN_TRAIL_SPAWN_TIME, MAX_TRAIL_SPAWN_TIME);
	m_canTrail = false;
}

Bullet::~Bullet()
{

}

void Bullet::Process(float deltaTime)
{
	Entity::Process(deltaTime);

	m_elapsedTime += deltaTime;
	if (m_elapsedTime >= m_trailSpawnTime)
	{
		m_canTrail = true;
	}
}

bool Bullet::CanTrail() const
{
	return m_canTrail;
}

void Bullet::SetTrail(bool v)
{
	m_canTrail = v;
	m_elapsedTime = 0;
}
