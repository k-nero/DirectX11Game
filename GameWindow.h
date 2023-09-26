#pragma once
#include <DirectXMath.h>
#include <memory>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IInputListener.h"
#include "InputSystem.h"

class GameWindow : public Window, public IInputListener
{
public: 
	GameWindow();
	~GameWindow();

	// Inherited via Window
	void OnCreate() override;
	void OnDestroy() override;
	void OnUpdate() override;
	void OnFocus() override;
	void OnUnFocus() override;
	// Inherited via IInputListener
	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
	void OnMouseMove(const DirectX::XMFLOAT2& delta_mouse_position) override;
	void OnRightMouseDown(const DirectX::XMFLOAT2& mouse_position) override;
	void OnRightMouseUp(const DirectX::XMFLOAT2& mouse_position) override;
	void OnLeftMouseDown(const DirectX::XMFLOAT2& mouse_position) override;
	void OnLeftMouseUp(const DirectX::XMFLOAT2& mouse_position) override;
private:
	GraphicsEngine* g_pGraphics_engine = nullptr;
private:
	std::shared_ptr<SwapChain> m_swap_chain = nullptr;
	std::shared_ptr<VertexBuffer> m_vb = nullptr;
	std::shared_ptr<VertexShader> m_vs = nullptr;
	std::shared_ptr<PixelShader> m_ps = nullptr;
	std::shared_ptr<ConstantBuffer> m_cb = nullptr;
	std::shared_ptr<IndexBuffer> m_ib = nullptr;

private:
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	DWORD m_old_time = 0;
	DWORD m_new_time = 0;
	float m_delta_time = 0.0f;

	float m_scale_cube = 1.0f;
};

