#include "InputSystem.h"

InputSystem::InputSystem()
{
}

void InputSystem::Update()
{
    if (GetKeyboardState(m_key_states))
    {
        for (int i = 0; i < 256; i++)
        {
            if (m_key_states[i] & 0x80)
            {
                for (auto& it : m_listeners)
                {
					it.second->OnKeyDown(i);
				}
			}
            else
            {
                if (m_key_states[i] != m_old_key_states[i])
                {
                    for (auto& it : m_listeners)
                    {
                        it.second->OnKeyUp(i);
                    }
               }
			}
        }
        _memccpy(m_old_key_states, m_key_states, sizeof(m_key_states), sizeof(m_key_states));
    }
}

void InputSystem::AddListener(IInputListener* listener)
{
    m_listeners.insert(std::pair<IInputListener*, IInputListener*>(std::forward<IInputListener*>(listener), std::forward<IInputListener*>(listener)));
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
