#pragma once
#ifndef __PLAYERSHIP_H__
#define __PLAYERSHIP_H__

#include "entity.h"

class PlayerShip : public Entity {
public:
	PlayerShip();
	PlayerShip(int width);
	~PlayerShip();

	void Process(float deltaTime);


};

#endif // __PLAYERSHIP_H__