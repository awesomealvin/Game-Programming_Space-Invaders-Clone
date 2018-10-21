// COMP710 GP 2D Framework 2018

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "logmanager.h"

// Library includes:
#include <cassert>
#include <string>

InputHandler::InputHandler()
	: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		SDL_JoystickClose(m_pGameController);
		m_pGameController = 0;
	}
}

bool
InputHandler::Initialise()
{
	int numControllesr = SDL_NumJoysticks();

	m_pGameController = SDL_JoystickOpen(0);

	if (!m_pGameController)
	{
		LogManager::GetInstance().Log("No controller detected!");
	}

	return (true);
}

void
InputHandler::ProcessInput(Game& game)
{
	// W02.1: Receive Input Events below...
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_JOYBUTTONDOWN)
		{
			// W02.3: Tell the game to fire a player bullet...
			if (e.jbutton.button == 10)
			{
				//game.FireSpaceShipBullet();
			}


		}
		else if (e.type == SDL_KEYDOWN) {
			// W02.1: Tell the game to move the space ship left...
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				game.MoveSpaceShipLeft();
			}

			// W02.1: Tell the game to move the space ship right...

			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				game.MoveSpaceShipRight();
			}

			if (e.key.keysym.sym == SDLK_SPACE && e.key.repeat == 0)
			{

				game.FireSpaceShipBullet();

			}

		}
		else if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				game.SetSpaceShipStationary();
			}

			if (e.key.keysym.sym == SDLK_RIGHT)
			{
				game.SetSpaceShipStationary();
			}
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				float x = e.button.x;
				float y = e.button.y;
				std::string msg = "Mouse Clicked at: (";
				msg += std::to_string(x);
				msg += ", ";
				msg += std::to_string(y);
				msg += ")";
				LogManager::GetInstance().Log(msg.c_str());

				game.FireSpaceMissile(x, y);
			}
		}
	}
}
