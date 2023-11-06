#pragma once
#include <Windows.h>
class Window
{
public:
	Window();
	bool Initialize();
	void Broadcast();
	bool Release();
	bool IsRunning() const;
	void SetHWND(HWND hwnd);
	RECT GetClient() const;
	virtual void OnCreate();
	virtual void OnDestroy();
	virtual void OnUpdate();
	virtual void OnFocus();
	virtual void OnUnFocus();
	virtual void OnResize();
	virtual RECT GetPhysicalScreensize();
	~Window();
protected:
	HWND m_hWnd{};
	bool m_isRunning = false;
};