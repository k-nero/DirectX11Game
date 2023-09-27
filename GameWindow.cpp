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
	m_camera = std::make_shared<Camera>(Camera({ 0, 0, 2 }, { 0, 1, 0 }, -90.0f, 0.0f, 1.0f, 0.2f));
	InputSystem::Get()->AddListener(this);
	InputSystem::Get()->ShowCursor(false);
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
	m_camera->UpdateViewMatrix();
	auto context = g_pGraphics_engine->GetImmediateDeviceContext();
	context->ClearRenderTargetView(m_swap_chain->GetRenderTargetView(), 0.0f, 0.3f, 0.4f, 1.0f);
	context->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	constant cbuffer{};
	cbuffer.time = 0.6f;
	cbuffer.m_world = DirectX::XMMatrixIdentity();
	cbuffer.m_view = m_camera->GetViewMatrix();
	cbuffer.m_projection = DirectX::XMMatrixPerspectiveFovLH(1.57f, ((float)(rc.right - rc.left) / (float)(rc.bottom - rc.top)), 0.1f, 1000.0f);

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
	m_camera->KeyControl(key, m_delta_time);
	if (key == VK_ESCAPE)
	{
		this->m_play_state = !this->m_play_state;
		InputSystem::Get()->ShowCursor(!this->m_play_state);
	}
}

void GameWindow::OnKeyUp(int key)
{

}

void GameWindow::OnMouseMove(const DirectX::XMFLOAT2& mouse_position)
{
	RECT rc = this->GetClient();
	POINT center = { (rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2 };
	if (m_play_state)
	{
		m_camera->MouseControl(mouse_position.x - center.x, mouse_position.y - center.y);
		InputSystem::Get()->SetCursorPosition(center);
	}

}

void GameWindow::OnRightMouseDown(const DirectX::XMFLOAT2& mouse_position)
{

}

void GameWindow::OnRightMouseUp(const DirectX::XMFLOAT2& mouse_position)
{

}

void GameWindow::OnLeftMouseDown(const DirectX::XMFLOAT2& mouse_position)
{

}

void GameWindow::OnLeftMouseUp(const DirectX::XMFLOAT2& mouse_position)
{

}
