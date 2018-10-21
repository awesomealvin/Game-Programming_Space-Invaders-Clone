#include "explosion.h"
#include "entity.h"
#include "animatedsprite.h"
#include "logmanager.h"

#include <cassert>

Explosion::Explosion() : Entity()
{

}

Explosion::~Explosion()
{
	delete m_animatedSprite;
	m_animatedSprite = 0;
}

bool Explosion::Initialise(AnimatedSprite* animatedSprite)
{
	assert(animatedSprite);
	m_animatedSprite = animatedSprite;
	int frameWidth = 64;
	m_animatedSprite->SetFrameWidth(frameWidth);
	m_animatedSprite->SetFrameHeight(frameWidth);
	m_animatedSprite->SetFrameSpeed(0.075);

	int frameCount = 5;
	for (int i = 0; i < frameCount; ++i)
	{
		m_animatedSprite->AddFrame(i * frameWidth);
	}
	
	return (true);
}

void Explosion::Process(float deltaTime)
{
	Entity::Process(deltaTime);
	m_animatedSprite->Process(deltaTime);
	if (!m_animatedSprite->IsAnimating())
	{
		//LogManager::GetInstance().Log("SET DEAD");
		m_dead = true;
	}
}

void Explosion::Draw(BackBuffer & backBuffer)
{
	assert(m_animatedSprite);
	m_animatedSprite->SetX(static_cast<int>(m_x));
	m_animatedSprite->SetY(static_cast<int>(m_y));
	m_animatedSprite->Draw(backBuffer);
}

float Explosion::GetSpriteWidth() const
{
	return m_animatedSprite->GetFrameWidth();
}

float Explosion::GetSpriteHeight() const
{
	return m_animatedSprite->GetFrameHeight();
}

void Explosion::SetPositionCenter(float x, float y)
{
	m_x = x - (GetSpriteWidth() / 2);
	m_y = y - (GetSpriteHeight() / 2);
}

