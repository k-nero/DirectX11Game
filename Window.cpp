#include "Window.h"

Window::Window()
{

}

__int64 _stdcall WndProc(HWND hWnd, unsigned int  message, unsigned __int64 wParam, __int64 lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			Window* window = (Window*) ((LPCREATESTRUCTW) lParam)->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (__int64) window);
			window->SetHWND(hWnd);
			window->OnCreate();
			break;
		}
		case WM_DESTROY:
		{
			Window* window = (Window*) GetWindowLongPtr(hWnd, GWLP_USERDATA);
			window->OnDestroy();
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool Window::Initialize()
{
	WNDCLASSEXW wc{};
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) 0x0005U;
	wc.hCursor = LoadCursor(0, ((LPWSTR) (0x7F00)));
	wc.hIcon = LoadIcon(0, ((LPWSTR) (0x7F00)));
	wc.hIconSm = LoadIcon(0, ((LPWSTR) (0x7F00)));
	wc.hInstance = 0;
	wc.lpszClassName = L"CXWindow";
	wc.lpszMenuName = 0;
	wc.style = 0x0003U;
	wc.lpfnWndProc = &WndProc;

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	m_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"CXWindow", L"DirectX 11 Game", ( 0x00CBF2EDL ), ((int) 0x80000000), ((int) 0x80000000), 1280, 720, 0, 0, 0, this);

	if (m_hWnd == 0)
	{
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	m_isRunning = true;

	return true;
}

void Window::Broadcast()
{
	MSG msg{};
	this->OnUpdate();
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool Window::Release()
{
	if (DestroyWindow(m_hWnd) == 0)
	{
		return true;
	}
	return false;
}

bool Window::IsRunning() const
{
	return m_isRunning;
}

void Window::SetHWND(HWND hwnd)
{
	this->m_hWnd = hwnd;
}

RECT Window::GetClient() const
{
	RECT rc{};
	GetClientRect(this->m_hWnd, &rc);
	return rc;
}

void Window::OnCreate()
{

}

void Window::OnDestroy()
{
	m_isRunning = false;
}

void Window::OnUpdate()
{

}

Window::~Window()
{

}
