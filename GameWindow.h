#pragma once
#include <DirectXMath.h>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

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
	SwapChain * m_swap_chain = nullptr;
	VertexBuffer* m_vb = nullptr;
};

