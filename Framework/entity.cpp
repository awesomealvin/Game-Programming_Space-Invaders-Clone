// COMP710 GP 2D Framework 2018

// This include:
#include "entity.h"

// Local includes:
#include "sprite.h"
#include "backbuffer.h"

// Library includes:
#include <cassert>
#include <cmath>

Entity::Entity()
	: m_pSprite(0)
	, m_x(0.0f)
	, m_y(0.0f)
	, m_velocityX(0.0f)
	, m_velocityY(0.0f)
	, m_dead(false)
{
	m_windowWidth = 0;

}

Entity::Entity(int windowWidth) : Entity()
{
	m_windowWidth = windowWidth;
}

Entity::~Entity()
{

	delete m_pSprite;
	m_pSprite = 0;

}

bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;
	m_radius = m_pSprite->GetWidth() / 2;

	return (true);
}

void
Entity::Process(float deltaTime)
{
	// W02.1: Generic position update, based upon velocity (and time).
	m_x += m_velocityX * deltaTime;
	m_y += m_velocityY * deltaTime;

}

void
Entity::Draw(BackBuffer& backBuffer)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->Draw(backBuffer);
}

void Entity::DrawRotation(BackBuffer & backBuffer, float angle)
{
	assert(m_pSprite);
	m_pSprite->SetX(static_cast<int>(m_x));
	m_pSprite->SetY(static_cast<int>(m_y));
	m_pSprite->DrawRotation(backBuffer, angle);
}

bool
Entity::IsCollidingWith(Entity& e)
{
	// W02.3: Generic Entity Collision routine.
	bool isColliding = false;

	// W02.3: Does this object collide with the e object?
	// W02.3: Create a circle for each entity (this and e).

	struct CenterPosition {
		float x;
		float y;
	};

	CenterPosition myPosition;
	myPosition.x = m_x + GetSpriteWidth() / 2;
	myPosition.y = m_y + GetSpriteHeight() / 2;
	
	CenterPosition ePosition;
	ePosition.x = e.GetPositionX() + e.GetSpriteWidth() / 2;
	ePosition.y = e.GetPositionY() + e.GetSpriteHeight() / 2;

	// W02.3: Check for intersection.
	// W02.3: Using circle-vs-circle collision detection.
	float distance = sqrt(pow((ePosition.x - myPosition.x), 2) + (pow((ePosition.y - myPosition.y), 2))) - m_radius - e.GetRadius();

	// W02.3: Return result of collision.
	if (distance <= 0)
	{
		isColliding = true;
	}

	return (isColliding); // W02.3 Change return value!
}

void
Entity::SetDead(bool dead)
{
	m_dead = dead;
	// TODO : SOUND - enemy_explosion.wav
}

bool Entity::IsDead() const
{
	return m_dead;
}

void
Entity::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}

void
Entity::SetPositionX(float x)
{
	m_x = x;
}

void
Entity::SetPositionY(float y)
{
	m_y = y;
}

void Entity::SetPositionCenter(float x, float y)
{
	m_x = x - (GetSpriteWidth() / 2);
	m_y = y - (GetSpriteHeight() / 2);
}

float
Entity::GetPositionX() const
{
	return (m_x);
}

float
Entity::GetPositionY() const
{
	return (m_y);
}

float
Entity::GetHorizontalVelocity() const
{
	return (m_velocityX);
}

float
Entity::GetVerticalVelocity() const
{
	return (m_velocityY);
}

void
Entity::SetHorizontalVelocity(float x)
{
	m_velocityX = x;
}

void
Entity::SetVerticalVelocity(float y)
{
	m_velocityY = y;
}

float Entity::GetPositionSpriteCenterX() const
{
	float width = static_cast<float>(m_pSprite->GetWidth());
	return (width / 2);
}

float Entity::GetSpriteHeight() const
{
	return m_pSprite->GetHeight();
}

float Entity::GetSpriteWidth() const
{
	return m_pSprite->GetWidth();
}

float Entity::GetCenterPositionX() const
{
	return m_x + (m_pSprite->GetWidth() / 2);
}

float Entity::GetCenterPositionY() const
{
	return m_y + (m_pSprite->GetHeight() / 2);;
}


float Entity::GetRadius() const
{
	return m_radius;
}

void Entity::Revive(float x, float y)
{
	m_dead = false;
	m_x = x;
	m_y = y;
}
