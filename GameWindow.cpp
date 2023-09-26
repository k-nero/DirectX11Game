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

	InputSystem::Get()->AddListener(this);

	g_pGraphics_engine = GraphicsEngine::Get();
	g_pGraphics_engine->Initialize();
	m_swap_chain = g_pGraphics_engine->CreateSwapChain();
	auto client = this->GetClient();
	m_swap_chain->Initialize(this->m_hWnd, client.right - client.left, client.bottom - client.top, false);

	Vertex list[] =
	{
		{ XMFLOAT3{-0.5f, -0.5f, -0.5f}, XMFLOAT3{1, 0, 0}},
		{ XMFLOAT3{-0.5f, 0.5f, -0.5f}, XMFLOAT3{0, 1, 0} },
		{ XMFLOAT3{0.5f, 0.5f, -0.5f}, XMFLOAT3{0, 0, 1} },
		{ XMFLOAT3{0.5f, -0.5f, -0.5f}, XMFLOAT3{1, 1, 1} },
		{ XMFLOAT3{0.5f, -0.5f, 0.5f}, XMFLOAT3{1, 1, 1} },
		{ XMFLOAT3{0.5f, 0.5f, 0.5f}, XMFLOAT3{0, 0, 1} },
		{ XMFLOAT3{-0.5f, 0.5f, 0.5f}, XMFLOAT3{0, 1, 0} },
		{ XMFLOAT3{-0.5f, -0.5f, 0.5f}, XMFLOAT3{1, 0, 0}},
	};

	unsigned int index_list[] =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		1, 6, 5,
		5, 2, 1,

		7, 0, 3,
		3, 4, 7,

		3, 2, 5,
		5, 4, 3,

		7, 6, 1,
		1, 0, 7,
	};
	unsigned int index_list_size = (sizeof(*RtlpNumberOf(index_list)));
	m_ib = g_pGraphics_engine->CreateIndexBuffer();
	m_ib->Load(index_list, index_list_size);

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

	constant cbuffer = { 0 };
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
	InputSystem::Get()->Update();
	auto context = g_pGraphics_engine->GetImmediateDeviceContext();
	context->ClearRenderTargetView(m_swap_chain->GetRenderTargetView(), 0.0f, 0.3f, 0.4f, 1.0f);
	context->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cbuffer{};
	cbuffer.time = 0.6f;
	cbuffer.m_world = XMMatrixTranslation(0.0f, 0.0f, 0.0f) * XMMatrixScaling(m_scale_cube, m_scale_cube, m_scale_cube) * XMMatrixRotationY(m_rot_y) * XMMatrixRotationX(m_rot_x);
	cbuffer.m_view = XMMatrixIdentity();
	cbuffer.m_projection = XMMatrixOrthographicLH((rc.right - rc.left) / 300.0f, (rc.bottom - rc.top) / 300.0f, 4, -4);
	m_cb->Update(context, &cbuffer);

	context->SetConstantBuffer(m_vs.get(), m_cb.get());
	context->SetConstantBuffer(m_ps.get(), m_cb.get());

	context->SetVertexShader(m_vs.get());
	context->SetPixelShader(m_ps.get());
	context->SetVertexBuffer(m_vb.get());
	context->SetIndexBuffer(m_ib.get());
	context->DrawIndexedTriangleList(m_ib.get()->GetIndexListSize(), 0, 0);

	m_swap_chain->Present(true);

	m_old_time = m_new_time;
	m_new_time = GetTickCount();

	m_delta_time = (m_old_time) ? ((m_new_time - m_old_time) / 100.0f) : 0;

	context = nullptr;
}

void GameWindow::OnFocus()
{
	InputSystem::Get()->AddListener(this);
}

void GameWindow::OnUnFocus()
{
	InputSystem::Get()->RemoveListener(this);
}

void GameWindow::OnKeyDown(int key)
{
	if (key == 'W')
	{
		m_rot_x += 0.2f * m_delta_time;
	}
	else if(key == 'S')
	{
		m_rot_x -= 0.2f * m_delta_time;
	}
	else if(key == 'A')
	{
		m_rot_y += 0.2f * m_delta_time;
	}
	else if (key == 'D')
	{
		m_rot_y -= 0.2f * m_delta_time;
	}
}

void GameWindow::OnKeyUp(int key)
{

}

void GameWindow::OnMouseMove(const DirectX::XMFLOAT2& delta_mouse_position)
{
	m_rot_x -= delta_mouse_position.y * m_delta_time * 0.01f;
	m_rot_y -= delta_mouse_position.x * m_delta_time * 0.01f;
}

void GameWindow::OnRightMouseDown(const DirectX::XMFLOAT2& mouse_position)
{
	this->m_scale_cube += 0.2f * m_delta_time;
}

void GameWindow::OnRightMouseUp(const DirectX::XMFLOAT2& mouse_position)
{

}

void GameWindow::OnLeftMouseDown(const DirectX::XMFLOAT2& mouse_position)
{
	this->m_scale_cube -= 0.2f * m_delta_time;
}

void GameWindow::OnLeftMouseUp(const DirectX::XMFLOAT2& mouse_position)
{

}
