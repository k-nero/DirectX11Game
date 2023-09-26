#pragma once
#include "IInputListener.h"
#include <map>
#include <Windows.h>
#include <DirectXMath.h>
class InputSystem
{
public:
	InputSystem();
	void Update();
	void AddListener(IInputListener* listener);
	void SetCursorPosition(const POINT& position);
	void ShowCursor(bool show);
	void RemoveListener(IInputListener* listener);
	~InputSystem();
public:
	static InputSystem* Get();
private:
	std::map<IInputListener*, IInputListener*> m_listeners;
	unsigned char m_key_states[256] = {};
	unsigned char m_old_key_states[256] = {};
private:
	DirectX::XMFLOAT2 old_mouse_pos = {};
	bool init_move = true;
};

