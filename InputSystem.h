#pragma once
#include "IInputListener.h"
#include <map>
#include <Windows.h>
class InputSystem
{
public:
	InputSystem();
	void Update();
	void AddListener(IInputListener* listener);
	void RemoveListener(IInputListener* listener);
	~InputSystem();
public:
	static InputSystem* Get();
private:
	std::map<IInputListener*, IInputListener*> m_listeners;
	unsigned char m_key_states[256] = {};
	unsigned char m_old_key_states[256] = {};
};

