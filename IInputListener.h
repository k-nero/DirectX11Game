#pragma once
__interface IInputListener
{
public:
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;
};