#include "InputSystem.h"

InputSystem::InputSystem()
{
}

void InputSystem::Update()
{
	POINT current_mouse_pos = {};
	GetCursorPos(&current_mouse_pos);

	if (init_move)
	{
		old_mouse_pos = { static_cast<float>(current_mouse_pos.x), static_cast<float>(current_mouse_pos.y) };
		init_move = false;
	}

	if (current_mouse_pos.x != old_mouse_pos.x || current_mouse_pos.y != old_mouse_pos.y)
	{
		DirectX::XMFLOAT2 mouse_pos = {static_cast<float> (current_mouse_pos.x) ,static_cast<float>(current_mouse_pos.y)};
		for (auto& it : m_listeners)
		{
			it.second->OnMouseMove(mouse_pos);
		}
	}

	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			for (auto& it : m_listeners)
			{
				if (i == VK_LBUTTON)
				{
					it.second->OnLeftMouseDown({ static_cast<float>(current_mouse_pos.x), static_cast<float>(current_mouse_pos.y) });
				}
				else if (i == VK_RBUTTON)
				{
					it.second->OnRightMouseDown({ static_cast<float>(current_mouse_pos.x), static_cast<float>(current_mouse_pos.y) });
				}
				else
				{
					it.second->OnKeyDown(i);
				}
			}
		}
		else
		{
			for (auto& it : m_listeners)
			{
				if (i == VK_LBUTTON)
				{
					it.second->OnLeftMouseUp({ static_cast<float>(current_mouse_pos.x), static_cast<float>(current_mouse_pos.y) });
				}
				else if (i == VK_RBUTTON)
				{
					it.second->OnRightMouseUp({ static_cast<float>(current_mouse_pos.x), static_cast<float>(current_mouse_pos.y) });
				}
				else
				{
					it.second->OnKeyUp(i);
				}
			}
		}
	}

}

void InputSystem::AddListener(IInputListener* listener)
{
	m_listeners.insert(std::pair<IInputListener*, IInputListener*>(std::forward<IInputListener*>(listener), std::forward<IInputListener*>(listener)));
}

void InputSystem::SetCursorPosition(const POINT& position)
{
	SetCursorPos(position.x, position.y);
}

void InputSystem::ShowCursor(bool show)
{
	::ShowCursor(show);
}

void InputSystem::RemoveListener(IInputListener* listener)
{
	std::map<IInputListener*, IInputListener*>::iterator it = m_listeners.find(listener);
	if (it != m_listeners.end())
	{
		m_listeners.erase(it);
	}
}

InputSystem::~InputSystem()
{
}

InputSystem* InputSystem::Get()
{
	static InputSystem s_input_system;
	return &s_input_system;
}
