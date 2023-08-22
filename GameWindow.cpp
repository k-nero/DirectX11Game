#include "GameWindow.h"

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 color;
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
		{ DirectX::XMFLOAT3{-0.5f, -0.5f, 0.0f}, DirectX::XMFLOAT3{1, 0, 0} },
		{ DirectX::XMFLOAT3{-0.5f, 0.5f, 0.0f}, DirectX::XMFLOAT3{0, 1, 0} },
		{ DirectX::XMFLOAT3{0.5f, -0.5f, 0.0f}, DirectX::XMFLOAT3{0, 0, 1} },
		{ DirectX::XMFLOAT3{0.5f, 0.5f, 0.0f}, DirectX::XMFLOAT3{1, 1, 1} }
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(list, sizeof(Vertex), ARRAYSIZE(list), shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

}

void GameWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vs->Release();
	m_ps->Release();
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
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawTriangleStrip(m_vb->GetVertexListSize(), 0);
	m_swap_chain->Present(true);
}

