#include "Window.h"

Window::Window() = default;

__int64 _stdcall WndProc(HWND hWnd, unsigned int  message, unsigned __int64 wParam, __int64 lParam)
{
	switch (message)
	{
		case 0x0001U:
		{
			Window* window = (Window*) ((LPCREATESTRUCTW) lParam)->lpCreateParams;
			SetWindowLongPtrW(hWnd, (-21), (__int64) window);
			window->SetHWND(hWnd);
			window->OnCreate();
			break;
		}
		case 0x0002U:
		{
			Window* window = (Window*) GetWindowLongPtrW(hWnd, -21);
			window->OnDestroy();
			PostQuitMessage(0);
			break;
		}
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);
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

	if (!RegisterClassExW(&wc))
	{
		return false;
	}

	m_hWnd = CreateWindowExW(( 0x00000300L ), L"CXWindow", L"DirectX 11 Game", (0x00CBF2EDL), ((int) 0x80000000), ((int) 0x80000000), 1280, 720, 0, 0, 0, this);

	if (m_hWnd == 0)
	{
		return false;
	}

	ShowWindow(m_hWnd, 0x5);
	UpdateWindow(m_hWnd);
	m_isRunning = true;

	return true;
}

void Window::Broadcast()
{
	tagMSG msg{};
	this->OnUpdate();
	while (PeekMessageW(&msg, 0, 0x0U, 0x0U, 0x0001U) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
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
	tagRECT rc{};
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

Window::~Window() = default;
