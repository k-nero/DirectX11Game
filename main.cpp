#if defined(_DEBUG)
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include "GameWindow.h"
#include <iostream>


#ifdef _DEBUG
int reportHook(int reportType, char* userMessage, int* retVal) {
	if (reportType == _CRT_ASSERT) {
		std::cout << userMessage << std::endl;
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
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	if (FAILED(hr))
	{
		return false;
	}
	GameWindow game;
	if (game.Initialize())
	{
		while (game.IsRunning())
		{
			game.Broadcast();
		}
	}
	CoUninitialize();
#if defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

