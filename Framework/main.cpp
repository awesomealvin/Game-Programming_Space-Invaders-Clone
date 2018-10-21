// COMP710 GP 2D Framework 2018

// Library includes:
#include <SDL.h>
#include <crtdbg.h>
#include <cstdlib>
#include <ctime>


// Local includes:
#include "game.h"
#include "logmanager.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(0));

	Game& gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		LogManager::GetInstance().Log("Game initialise failed!");

		return (1);
	}
	
	while (gameInstance.DoGameLoop())
	{
		// No body.
	}

	Game::DestroyInstance();

	return (0);
}
