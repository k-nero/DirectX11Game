#include "GameWindow.h"

GameWindow::GameWindow()
{

}

GameWindow::~GameWindow()
{
	if (m_swap_chain)
	{
		m_swap_chain = nullptr;
	}
}

void GameWindow::OnCreate()
{
	Window::OnCreate();
	GraphicsEngine::Get()->Initialize();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();
	auto client = this->GetClient();
	m_swap_chain->Initialize(this->m_hWnd, client.right - client.left, client.bottom - client.top, false);
}

void GameWindow::OnDestroy()
{
	Window::OnDestroy();
	m_swap_chain->Release();
	GraphicsEngine::Get()->Shutdown();
}

void GameWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetView(m_swap_chain->GetRenderTargetView(), 1.0f, 0.0f, 0.0f, 0.5f);
	m_swap_chain->Present(true);
}

