#include "PlayerBulletTrailParticle.h"
#include "MyUtility.h"
#include "Vector2.h"
#include "logmanager.h"
#include <string>

PlayerBulletTrailParticle::PlayerBulletTrailParticle() :
	MIN_ANGLE(90.0f - 15.0f), // 90 = down
	MAX_ANGLE(90.0f + 15.0f)  // 90 = south
{
	m_minAliveTime = 0.1f;
	m_maxAliveTime = 0.5f;
}


PlayerBulletTrailParticle::~PlayerBulletTrailParticle()
{
}

void PlayerBulletTrailParticle::Revive(float x, float y)
{
	Particle::Revive(x, y);
	m_angleVelocity = MyUtility::GetInstance().RandomFloat(MIN_ANGLE, MAX_ANGLE);

	Vector2 velocity = Vector2::CalculateVectorFromAngle(m_angleVelocity);
	std::string msg = std::to_string(m_angleVelocity);
	LogManager::GetInstance().Log(msg.c_str());


	velocity *= 100;
	SetHorizontalVelocity(velocity.GetX());
	SetVerticalVelocity(velocity.GetY());

	//m_maxAliveTime = MyUtility::GetInstance().RandomFloat(MIN_ALIVE_TIME, MAX_ALIVE_TIME);
}
