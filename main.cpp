#if defined(_DEBUG)
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include "GameWindow.h"


#ifdef _DEBUG
#include <iostream>
static int reportHook(int reportType, char* userMessage, int* ) {
	if (reportType == _CRT_ASSERT) {
		std::cout << userMessage << std::endl;
		return TRUE;
	}
	return FALSE;
}
#endif // DEBUG

int WINAPI WinMain(_In_ HINSTANCE , _In_opt_ HINSTANCE , _In_ PSTR , _In_ int )
{

#if defined(_DEBUG)
	int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmpFlag);

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

