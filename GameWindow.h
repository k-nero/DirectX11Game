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

class GameWindow : public Window
{
public: 
	GameWindow();
	~GameWindow();

	// Inherited via Window
	void OnCreate() override;
	void OnDestroy() override;
	void OnUpdate() override;
private:
	GraphicsEngine* g_pGraphics_engine = nullptr;
private:
	std::shared_ptr<SwapChain> m_swap_chain = nullptr;
	std::shared_ptr<VertexBuffer> m_vb = nullptr;
	std::shared_ptr<VertexShader> m_vs = nullptr;
	std::shared_ptr<PixelShader> m_ps = nullptr;
	std::shared_ptr<ConstantBuffer> m_cb = nullptr;
	std::shared_ptr<IndexBuffer> m_ib = nullptr;
};

