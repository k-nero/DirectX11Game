#include "GameWindow.h"
#include <iostream>

int main(int argc, char** argv)
{
	GameWindow game;
	if (game.Initialize())
	{
		while (game.IsRunning())
		{
			game.Broadcast();
		}
	}
	return 0;
}