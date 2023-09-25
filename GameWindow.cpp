#include "GameWindow.h"

using namespace DirectX;

__declspec(align(16)) struct constant
{
	float time;
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;
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

	m_ib = g_pGraphics_engine->CreateIndexBuffer();

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
	g_pGraphics_engine->Shutdown();
}

void GameWindow::OnUpdate()
{
	Window::OnUpdate();
	RECT rc = this->GetClient();

	auto context = g_pGraphics_engine->GetImmediateDeviceContext();
	context->ClearRenderTargetView(m_swap_chain->GetRenderTargetView(), 0.0f, 0.3f, 0.4f, 1.0f);
	context->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cbuffer{};
	cbuffer.time = 0.6f;
	cbuffer.m_world = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	cbuffer.m_view = XMMatrixIdentity();
	cbuffer.m_projection = XMMatrixOrthographicLH((rc.right - rc.left)/400.0f, (rc.bottom - rc.top)/200.0f, 4, -4);
	m_cb->Update(context, &cbuffer);

	context->SetConstantBuffer(m_vs.get(), m_cb.get());
	context->SetConstantBuffer(m_ps.get(), m_cb.get());

	context->SetVertexShader(m_vs.get());
	context->SetPixelShader(m_ps.get());
	context->SetVertexBuffer(m_vb.get());
	context->DrawTriangleStrip(m_vb->GetVertexListSize(), 0);

	m_swap_chain->Present(true);
	context = nullptr;
}