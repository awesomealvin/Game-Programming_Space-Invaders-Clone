#ifndef __PARTICLEEMITTER_H__
#define __PARTICLEEMITTER_H__

#include <vector>
#include "particle.h"
#include "AlienExplosionParticle.h"
#include "PlayerBulletTrailParticle.h"

class ParticleEmitter {
public:
	ParticleEmitter();
	~ParticleEmitter();

	bool Initialise(BackBuffer* backBuffer);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void CreateAlienExplosion(float x, float y);

	void CreateBulletTrail(float x, float y);

private:
	const float MAX_ALIEN_EXPLOSION_PARTICLES;
	AlienExplosionParticle** m_alienExplosionParticles;

	const float MAX_BULLET_TRAIL_PARTICLES;
	PlayerBulletTrailParticle** m_bulletTrailParticles;

};

#endif // __PARTICLEEMITTER_H__
