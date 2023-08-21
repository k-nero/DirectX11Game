#include "GameWindow.h"

struct vec3
{
	float x, y, z;
};

struct Vertex
{
	DirectX::XMFLOAT3 position;
};

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

	Vertex list[] =
	{
		DirectX::XMFLOAT3{-0.5f, -0.5f, 0.0f},
		DirectX::XMFLOAT3{0.0f, 0.5f, 0.0f},
		DirectX::XMFLOAT3{0.5f, -0.5f, 0.0f}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	GraphicsEngine::Get()->CreateShaders();
	void* shader_byte_code = nullptr;
	unsigned size_shader = 0;
	GraphicsEngine::Get()->GetShaderBufferAndSize(&shader_byte_code, &size_shader);
	m_vb->Load(list, sizeof(Vertex), ARRAYSIZE(list), shader_byte_code, size_shader);
}

void GameWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vb->Release();
	m_swap_chain->Release();
	GraphicsEngine::Get()->Shutdown();
}

void GameWindow::OnUpdate()
{
	Window::OnUpdate();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetView(m_swap_chain->GetRenderTargetView(), 0.0f, 0.3f, 0.4f, 1.0f);
	RECT rc = this->GetClient();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::Get()->SetShaders();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleList(m_vb->GetVertexListSize(), 0);
	m_swap_chain->Present(true);
}

