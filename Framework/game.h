// COMP710 GP 2D Framework 2018
#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "particleemitter.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class PlayerShip;
class Enemy;
class Bullet;
class Explosion;
class SpaceMissile;

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	void InitialiseFMOD();
	bool DoGameLoop();
	void Quit();

	void MoveSpaceShipLeft();
	void MoveSpaceShipRight();
	void SetSpaceShipStationary();
	void FireSpaceShipBullet();
	void FireSpaceMissile(float x, float y);

	void SpawnEnemy(int x, int y);
	void SpawnExplosion(int x, int y);

	void InitialisePools();

	void ResetEnemies();
	
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	//Member Data:
public:


protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	// Game Entities:
	// W02.1: Add a PlayerShip field. 
	PlayerShip* playerShip;

	// W02.2: Add an alien enemy container field.
	std::vector<Enemy*> m_enemyContainer;

	// W02.3: Add a bullet container field.
	std::vector<Bullet*> m_bulletContainer;

	std::vector<Explosion*> m_explosionContainer;

	Bullet* m_bulletPool;
	const int BULLET_POOL_SIZE;

	Enemy* m_enemyPool;
	const int ENEMY_POOL_SIZE;

	ParticleEmitter m_particleEmitter;

	SpaceMissile* m_spaceMissilePool;
	const int MISSILE_POOL_SIZE;

private:

};

#endif // __GAME_H__
