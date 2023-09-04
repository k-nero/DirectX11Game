#include "GameWindow.h"

using namespace DirectX;

__declspec(align(16)) struct constant
{
	unsigned int time;
};

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT3 color;
};

GameWindow::GameWindow() = default;

GameWindow::~GameWindow()
{
	
}

void GameWindow::OnCreate()
{
	Window::OnCreate();
	g_pGraphics_engine = GraphicsEngine::Get();
	g_pGraphics_engine->Initialize();
	m_swap_chain = g_pGraphics_engine->CreateSwapChain();
	auto client = this->GetClient();
	m_swap_chain->Initialize(this->m_hWnd, client.right - client.left, client.bottom - client.top, false);

	Vertex list[] =
	{
		{ XMFLOAT3{-0.5f, -0.5f, 0.0f}, XMFLOAT3{1, 0, 0} },
		{ XMFLOAT3{-0.5f, 0.5f, 0.0f}, XMFLOAT3{0, 1, 0} },
		{ XMFLOAT3{0.5f, -0.5f, 0.0f}, XMFLOAT3{0, 0, 1} },
		{ XMFLOAT3{0.5f, 0.5f, 0.0f}, XMFLOAT3{1, 1, 1} }
	};

	m_vb = g_pGraphics_engine->CreateVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	g_pGraphics_engine->CompileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = g_pGraphics_engine->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(list, sizeof(Vertex), (sizeof(*RtlpNumberOf(list))), shader_byte_code, size_shader);
	g_pGraphics_engine->ReleaseCompiledShader();

	g_pGraphics_engine->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_ps = g_pGraphics_engine->CreatePixelShader(shader_byte_code, size_shader);
	g_pGraphics_engine->ReleaseCompiledShader();

	constant cbuffer = {0};
	m_cb = g_pGraphics_engine->CreateConstantBuffer();
	m_cb->Load(&cbuffer, sizeof(constant));
}

void GameWindow::OnDestroy()
{
	Window::OnDestroy();
	m_vs->Release();
	m_ps->Release();
	m_vb->Release();
	m_swap_chain->Release();
	g_pGraphics_engine->Shutdown();
}

void GameWindow::OnUpdate()
{
	Window::OnUpdate();
	RECT rc = this->GetClient();

	auto context = g_pGraphics_engine->GetImmediateDeviceContext();
	context->ClearRenderTargetView(m_swap_chain->GetRenderTargetView(), 0.0f, 0.3f, 0.4f, 1.0f);
	context->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cbuffer = {0};
	cbuffer.time = GetTickCount();
	m_cb->Update(context, &cbuffer);
	context->SetConstantBuffer(m_vs, m_cb);
	context->SetConstantBuffer(m_ps, m_cb);

	context->SetVertexShader(m_vs);
	context->SetPixelShader(m_ps);
	context->SetVertexBuffer(m_vb);
	context->DrawTriangleStrip(m_vb->GetVertexListSize(), 0);

	m_swap_chain->Present(true);
	context = nullptr;
}