#include "Window.h"

Window::Window()
{

}

__int64 _stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			Window* window = (Window*) ((LPCREATESTRUCT) lParam)->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR) window);
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
	WNDCLASSEX wc{};
	wc.cbClsExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"CXWindow";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &WndProc;

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	m_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"CXWindow", L"DirectX 11 Game", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, NULL, this);

	if (m_hWnd == 0)
	{
		return false;
	}

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	m_isRunning = true;

	return true;
}

bool Window::Broadcast()
{
	MSG msg{};
	this->OnUpdate();
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
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
