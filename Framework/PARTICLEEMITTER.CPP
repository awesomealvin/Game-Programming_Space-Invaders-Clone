#include "particleemitter.h"
#include "backbuffer.h"
#include "MyUtility.h"
#include "Vector2.h"

ParticleEmitter::ParticleEmitter() :
	MAX_ALIEN_EXPLOSION_PARTICLES(64),
	MAX_BULLET_TRAIL_PARTICLES(64)
{
}

ParticleEmitter::~ParticleEmitter()
{
	// Delete Alien Explosion Particles
	for (int i = 0; i < MAX_ALIEN_EXPLOSION_PARTICLES; ++i)
	{

		delete m_alienExplosionParticles[i];

	}
	delete[] m_alienExplosionParticles;

	// Delete Bullet Trail Particles
	for (int i = 0; i < MAX_BULLET_TRAIL_PARTICLES; ++i)
	{
		delete m_bulletTrailParticles[i];
	}
	delete[] m_bulletTrailParticles;



	
}

bool ParticleEmitter::Initialise(BackBuffer * backBuffer)
{
	// Initialise alien explosion
	m_alienExplosionParticles = new AlienExplosionParticle*[MAX_ALIEN_EXPLOSION_PARTICLES];
	for (int i = 0; i < MAX_ALIEN_EXPLOSION_PARTICLES; ++i)
	{
		Sprite* sprite = backBuffer->CreateSprite("assets\\alienfragment.png");

		m_alienExplosionParticles[i] = new AlienExplosionParticle();
		m_alienExplosionParticles[i]->Initialise(sprite);
		m_alienExplosionParticles[i]->SetDead(true);
	}

	// Initialise Bullet Trails
	m_bulletTrailParticles = new PlayerBulletTrailParticle*[MAX_BULLET_TRAIL_PARTICLES];
	for (int i = 0; i < MAX_BULLET_TRAIL_PARTICLES; ++i)
	{
		Sprite* sprite = backBuffer->CreateSprite("assets\\playerbullettrail.png");

		m_bulletTrailParticles[i] = new PlayerBulletTrailParticle();
		m_bulletTrailParticles[i]->Initialise(sprite);
		m_bulletTrailParticles[i]->SetDead(true);
	}

	return true;
}

void ParticleEmitter::Process(float deltaTime)
{
	// Process Alien Explosion Particles
	for (int i = 0; i < MAX_ALIEN_EXPLOSION_PARTICLES; ++i)
	{
		if (!m_alienExplosionParticles[i]->IsDead())
		{
			m_alienExplosionParticles[i]->Process(deltaTime);
		}
	}

	// Process Bullet Trail Particles
	for (int i = 0; i < MAX_BULLET_TRAIL_PARTICLES; ++i)
	{
		PlayerBulletTrailParticle* b = m_bulletTrailParticles[i];

		if (!b->IsDead())
		{
			b->Process(deltaTime);
		}
	}
}

void ParticleEmitter::Draw(BackBuffer & backBuffer)
{
	// Draw Alien Explosion Particles
	for (int i = 0; i < MAX_ALIEN_EXPLOSION_PARTICLES; ++i)
	{
		if (!m_alienExplosionParticles[i]->IsDead())
		{
			m_alienExplosionParticles[i]->DrawRotation(backBuffer);
		}
	}

	// Draw Bullet Trail Particles
	for (int i = 0; i < MAX_BULLET_TRAIL_PARTICLES; ++i)
	{
		PlayerBulletTrailParticle* b = m_bulletTrailParticles[i];

		if (!b->IsDead())
		{
			b->Draw(backBuffer);
		}
	}
}

void ParticleEmitter::CreateAlienExplosion(float x, float y)
{
	int particleAmount = MyUtility::GetInstance().RandomInt(10, 15);

	int particles = 0;
	for (int i = 0; i < MAX_ALIEN_EXPLOSION_PARTICLES && particles < particleAmount; ++i)
	{
		AlienExplosionParticle* p = m_alienExplosionParticles[i];
		if (p->IsDead()) 
  		{

			p->Revive(x, y);

			float angle = MyUtility::GetInstance().RandomFloat(0, 360);
			
			Vector2 vel = Vector2::CalculateVectorFromAngle(angle);
				
			vel *= MyUtility::GetInstance().RandomFloat(50, 120);

			p->SetHorizontalVelocity(vel.GetX());
			p->SetVerticalVelocity(vel.GetY());
			++particles;
		}
	}
}

void ParticleEmitter::CreateBulletTrail(float x, float y)
{
	int particleAmount = MyUtility::GetInstance().RandomInt(1, 2);

	int particles = 0;
	for (int i = 0; i < MAX_BULLET_TRAIL_PARTICLES && particles < particleAmount; ++i)
	{
		PlayerBulletTrailParticle* p = m_bulletTrailParticles[i];

		if (p->IsDead())
		{

			p->Revive(x, y);

			++particles;
		}
	}
}
