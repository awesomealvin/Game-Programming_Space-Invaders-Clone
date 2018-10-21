#include "playership.h"

#include "sprite.h"

PlayerShip::PlayerShip() : Entity()
{

}

PlayerShip::PlayerShip(int width) : Entity(width)
{
	
}


PlayerShip::~PlayerShip()
{
	Entity::~Entity();
}

void PlayerShip::Process(float deltaTime)
{
	Entity::Process(deltaTime);

	// Stops the player from going outside of the window... Assuming the width is 800 :D
	if (m_x < 0)
	{
		m_x = 0;
	}
	// Need the width because the anchor point is at the top left.
	if (m_x + m_pSprite->GetWidth() > m_windowWidth)
	{
		m_x = m_windowWidth - m_pSprite->GetWidth();
	}

}


