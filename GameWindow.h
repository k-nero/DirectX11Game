#pragma once
#include <DirectXMath.h>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

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
	SwapChain * m_swap_chain = nullptr;
	VertexBuffer* m_vb = nullptr;
	VertexShader* m_vs = nullptr;
	PixelShader* m_ps = nullptr;
};

