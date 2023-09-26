#pragma once
#include <DirectXMath.h>

__interface IInputListener
{
public:
	virtual void OnKeyDown(int key) = 0;
	virtual void OnKeyUp(int key) = 0;

	virtual void OnMouseMove(const DirectX::XMFLOAT2& mouse_position) = 0;
	virtual void OnRightMouseDown(const DirectX::XMFLOAT2& mouse_position) = 0;
	virtual void OnRightMouseUp(const DirectX::XMFLOAT2& mouse_position) = 0;
	virtual void OnLeftMouseDown(const DirectX::XMFLOAT2& mouse_position) = 0;
	virtual void OnLeftMouseUp(const DirectX::XMFLOAT2& mouse_position) = 0;
};