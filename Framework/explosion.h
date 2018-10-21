#pragma once
#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "entity.h"
#include "animatedsprite.h"

class Explosion : public Entity {

public:
	Explosion();
	~Explosion();

	bool Initialise(AnimatedSprite* animatedSprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);


	AnimatedSprite* m_animatedSprite;

	float GetSpriteWidth() const;
	float GetSpriteHeight() const;

	void SetPositionCenter(float x, float y);

};

#endif // __EXPLOSION_H__