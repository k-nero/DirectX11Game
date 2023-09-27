#if defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include "GameWindow.h"
#include <iostream>


#ifdef _DEBUG
int reportHook(int reportType, char* userMessage, int* retVal) {
	if (reportType == _CRT_ASSERT) {
		// Print detailed error message
		//_CrtDbgReport(_CRT_ASSERT, NULL, 0, NULL, "%s", userMessage); [wrong] It's a recursive function that causes an infinite loop.
		std::cout << userMessage << std::endl; // <-- This should show a message box, but it doesn't show because 'reportHook' is not called.
		return TRUE;
	}
	return FALSE;
}
#endif // DEBUG


int __stdcall WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow)
{

#if defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtSetReportHook(&reportHook);
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