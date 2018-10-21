// COMP710 GP 2D Framework 2018

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "playership.h"
#include "enemy.h"
#include "bullet.h"
#include "fmod.hpp"
#include "animatedsprite.h"
#include "explosion.h"
#include "MyUtility.h"
#include "SpaceMissile.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>


// Static Members:
Game* Game::sm_pInstance = 0;

FMOD_RESULT result;
FMOD::System* soundSystem = NULL;
FMOD::Channel* channel = 0;
FMOD::Sound* soundHit, *soundPlayerShoot;
void* extradriverdata = 0;


Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
	: m_pBackBuffer(0)
	, m_pInputHandler(0)
	, m_looping(true)
	, m_executionTime(0)
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_FPS(0)
	, m_numUpdates(0)
	, m_lastTime(0)
	, m_lag(0)
	, BULLET_POOL_SIZE(16)
	, ENEMY_POOL_SIZE(100)
	, MISSILE_POOL_SIZE(8)
{

}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete playerShip;
	playerShip = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	LogManager::DestroyInstance();
	MyUtility::DestroyInstance();

	for (std::vector<Enemy*>::iterator it = m_enemyContainer.begin(); it != m_enemyContainer.end(); ++it)
	{
		delete *it;
		*it = 0;
	}
	m_enemyContainer.clear();

	for (std::vector<Bullet*>::iterator it = m_bulletContainer.begin(); it != m_bulletContainer.end(); ++it)
	{
		delete *it;
		*it = 0;
	}
	m_bulletContainer.clear();

	// RELEASE SOUNDS
	result = soundHit->release();
	result = soundSystem->close();
	result = soundSystem->release();

	// DELETE POOLS
	delete[] m_bulletPool;
	m_bulletPool = 0;
	delete[] m_enemyPool;
	m_enemyPool = 0;
	delete[] m_spaceMissilePool;
	m_spaceMissilePool = 0;

}

bool
Game::Initialise()
{
	const int width = 800;
	const int height = 600;


	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	// W02.1: Load the player ship sprite.
	// For example: Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");
	Sprite* playerSprite = m_pBackBuffer->CreateSprite("assets\\playership.png");

	// W02.1: Create the player ship instance.
	playerShip = new PlayerShip(width);
	playerShip->Initialise(playerSprite);
	playerShip->SetPosition(width / 2, 500);

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	// INITIALISE SOUND
	InitialiseFMOD();
	result = soundSystem->createSound("assets\\hit_marker_sound.wav", FMOD_CREATESAMPLE, NULL, &soundHit);
	result = soundSystem->createSound("assets\\player_shoot.wav", FMOD_CREATESAMPLE, NULL, &soundPlayerShoot);

	// INITIALISE POOLS
	InitialisePools();

	//// W02.2: Spawn four rows of 14 alien enemies.
	ResetEnemies();

	// Initialise Particle Emitter
	m_particleEmitter.Initialise(m_pBackBuffer);


	return (true);

}

void Game::InitialisePools()
{
	// INITIALISE BULLETS
	m_bulletPool = new Bullet[BULLET_POOL_SIZE];
	for (int i = 0; i < BULLET_POOL_SIZE; ++i)
	{
		Sprite* bulletSprite = m_pBackBuffer->CreateSprite("assets\\playerbullet.png");

		m_bulletPool[i];
		m_bulletPool[i].Initialise(bulletSprite);
		m_bulletPool[i].SetDead(true);
	}

	// INITIALISE ENEMIES
	m_enemyPool = new Enemy[ENEMY_POOL_SIZE];
	for (int i = 0; i < ENEMY_POOL_SIZE; ++i)
	{
		// W02.2: Load the alien enemy sprite file.
		Sprite* enemySprite = m_pBackBuffer->CreateSprite("assets\\alienenemy.png");

		// W02.2: Create a new Enemy object. 
		m_enemyPool[i];
		m_enemyPool[i].Initialise(enemySprite);
		m_enemyPool[i].SetDead(true);
	}

	// INITIALISE MISSILES
	m_spaceMissilePool = new SpaceMissile[MISSILE_POOL_SIZE];
	for (int i = 0; i < MISSILE_POOL_SIZE; ++i)
	{
		Sprite* missileSprite = m_pBackBuffer->CreateSprite("assets\\playermissile.png");

		m_spaceMissilePool[i];
		m_spaceMissilePool[i].Initialise(missileSprite);
		m_spaceMissilePool[i].SetDead(true);
	}

}

void Game::ResetEnemies()
{
	float defaultX = 120;
	float incrementX = 40;
	float currentX = defaultX;
	float startY = 50;
	float yIncrement = 50;
	for (int i = 0; i < 4; ++i)
	{
		for (int k = 0; k < 14; ++k)
		{
			SpawnEnemy(currentX, startY);
		
			currentX += incrementX;

		}
		startY += yIncrement;
		currentX = defaultX;
	}
}

void Game::InitialiseFMOD()
{
	result = FMOD::System_Create(&soundSystem);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error!");
		exit(-1);
	}

	result = soundSystem->init(32, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error!");
		exit(-1);
	}

	//result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}

		Draw(*m_pBackBuffer);
	}

	//	SDL_Delay(1);

	return (m_looping);
}

void
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	// Update the game world simulation:

	// W02.1: Update player...
	playerShip->Process(deltaTime);

	// PROCESS BULLET
	for (int i = 0; i < BULLET_POOL_SIZE; ++i)
	{
		if (!m_bulletPool[i].IsDead()) 
		{
			// Process alive bullets
			m_bulletPool[i].Process(deltaTime);

			// Delete If out of screen
			if (m_bulletPool[i].GetPositionY() < (0 - m_bulletPool[i].GetSpriteHeight()))
			{
				m_bulletPool[i].SetDead(true);
			}

			// Check for collision
			for (int k = 0; k < ENEMY_POOL_SIZE; ++k)
			{
				if (!m_enemyPool[k].IsDead())
				{
					if (m_bulletPool[i].IsCollidingWith(m_enemyPool[k]))
					{
						m_bulletPool[i].SetDead(true);
						m_enemyPool[k].SetDead(true);

						result = soundSystem->playSound(soundHit, 0, false, &channel);

						// Spawn Explosion
						AnimatedSprite* explosionSprite = m_pBackBuffer->CreateAnimatedSprite("assets\\explosion.png");
						Explosion *explosion = new Explosion();
						explosion->Initialise(explosionSprite);
						float x = m_enemyPool[k].GetCenterPositionX();
						float y = m_enemyPool[k].GetCenterPositionY();
						explosion->SetPositionCenter(x, y);
						m_explosionContainer.push_back(explosion);

						m_particleEmitter.CreateAlienExplosion(x, y);
					}
				}
			}

			// Traails!
			if (m_bulletPool[i].CanTrail())
			{
				m_particleEmitter.CreateBulletTrail(m_bulletPool[i].GetCenterPositionX(), m_bulletPool[i].GetCenterPositionY());
				m_bulletPool[i].SetTrail(false);
			}

		}
	}

	

	// PROCESS EXPLOSIONS
	for (std::vector<Explosion*>::iterator it = m_explosionContainer.begin(); it != m_explosionContainer.end();)
	{
		Explosion* explosion = *it;
		explosion->Process(deltaTime);

		// TODO :
		// W02.3: Remove any dead explosions from the container...
		if (explosion->IsDead())
		{
			it = m_explosionContainer.erase(it);
			delete explosion;
			explosion = 0;
		}
		else
		{
			++it;
		}
	}

	// PROCESS MISSILES
	for (int i = 0; i < MISSILE_POOL_SIZE; ++i)
	{
		if (!m_spaceMissilePool[i].IsDead())
		{
			m_spaceMissilePool[i].Process(deltaTime);
		}
	}

	// SOUND STUFF
	soundSystem->update();

	// Process Particles
	m_particleEmitter.Process(deltaTime);
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();


	for (int i = 0; i < ENEMY_POOL_SIZE; ++i)
	{
		if (!m_enemyPool[i].IsDead())
		{
			m_enemyPool[i].Draw(backBuffer);
		}
	}

	for (int i = 0; i < BULLET_POOL_SIZE; ++i)
	{
		if (!m_bulletPool[i].IsDead())
		{
			m_bulletPool[i].Draw(backBuffer);
		}
	}

	for (std::vector<Explosion*>::iterator it = m_explosionContainer.begin(); it != m_explosionContainer.end(); ++it)
	{
		Explosion* explosion = *it;
		explosion->Draw(backBuffer);
	}

	// W02.1: Draw the player ship...
	playerShip->Draw(backBuffer);

	// Draw Particles
	m_particleEmitter.Draw(backBuffer);

	// DRAW MISSILES
	for (int i = 0; i < MISSILE_POOL_SIZE; ++i)
	{
		if (!m_spaceMissilePool[i].IsDead())
		{
			m_spaceMissilePool[i].Draw(backBuffer);
		}
	}

	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void
Game::MoveSpaceShipLeft()
{
	// W02.1: Tell the player ship to move left.
	playerShip->SetHorizontalVelocity(-100);
}

void Game::MoveSpaceShipRight()
{
	playerShip->SetHorizontalVelocity(100);
}

void Game::SetSpaceShipStationary()
{
	playerShip->SetHorizontalVelocity(0);
}


// W02.3: Space a Bullet in game.
void
Game::FireSpaceShipBullet()
{
	bool spawned = false;
	for (int i = 0; i < BULLET_POOL_SIZE && !spawned; ++i)
	{
		if (m_bulletPool[i].IsDead())
		{
			float xPosition = playerShip->GetPositionX();
			xPosition += playerShip->GetPositionSpriteCenterX();
			xPosition -= m_bulletPool[i].GetPositionSpriteCenterX();
			m_bulletPool[i].Revive(xPosition, playerShip->GetPositionY());
			m_bulletPool[i].SetVerticalVelocity(-200);
			spawned = true;
		}
	}

	// Play Sound
	result = soundSystem->playSound(soundPlayerShoot, 0, false, &channel);

}

void Game::FireSpaceMissile(float x, float y)
{
	bool freeMissile = false;
	for (int i = 0; i < MISSILE_POOL_SIZE && !freeMissile; ++i)
	{
		if (m_spaceMissilePool[i].IsDead())
		{
			freeMissile = true;
			
			m_spaceMissilePool[i].Revive(playerShip->GetCenterPositionX(), playerShip->GetCenterPositionY());
			m_spaceMissilePool[i].SetTarget(x, y);
		}
	}
}

// W02.2: Spawn a Enemy in game.
void
Game::SpawnEnemy(int x, int y)
{
	bool spawned = false;
	for (int i = 0; i < ENEMY_POOL_SIZE && !spawned; ++i)
	{
		if (m_enemyPool[i].IsDead())
		{
			m_enemyPool[i].Revive(x, y);
			spawned = true;
		}
	}
}


