#if defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include "GameWindow.h"
#include <iostream>

int __stdcall WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow)
{

#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif
	GameWindow game;
	if (game.Initialize())
	{
		while (game.IsRunning())
		{
			game.Broadcast();
		}
	}

#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}