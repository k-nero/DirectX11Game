#include "GameWindow.h"

using namespace DirectX;

GameWindow::GameWindow() = default;

void GameWindow::OnCreate()
{
	Window::OnCreate();
	InputSystem::Get()->AddListener(this);
	InputSystem::Get()->ShowCursor(false);
	g_pGraphics_engine = GraphicsEngine::Get();
	m_texture = g_pGraphics_engine->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
	m_mesh = g_pGraphics_engine->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj");

	m_swap_chain = g_pGraphics_engine->GetRenderer()->CreateSwapChain();
	auto client = this->GetClient();
	m_swap_chain->Initialize(this->m_hWnd, client.right - client.left, client.bottom - client.top, false);

	//DirectX::XMFLOAT3 position_list[] =
	//{
	//	 DirectX::XMFLOAT3{-0.5f, -0.5f, -0.5f},
	//	 DirectX::XMFLOAT3{-0.5f, 0.5f, -0.5f},
	//	 DirectX::XMFLOAT3{0.5f, 0.5f, -0.5f},
	//	 DirectX::XMFLOAT3{0.5f, -0.5f, -0.5f},

	//	 DirectX::XMFLOAT3{0.5f, -0.5f, 0.5f},
	//	 DirectX::XMFLOAT3{0.5f, 0.5f, 0.5f},
	//	 DirectX::XMFLOAT3{-0.5f, 0.5f, 0.5f},
	//	 DirectX::XMFLOAT3{-0.5f, -0.5f, 0.5f}
	//};

	//DirectX::XMFLOAT2 texcoord_list[] =
	//{
	//	DirectX::XMFLOAT2{0.0f, 0.0f},
	//	DirectX::XMFLOAT2{0.0f, 1.0f},
	//	DirectX::XMFLOAT2{1.0f, 0.0f},
	//	DirectX::XMFLOAT2{1.0f, 1.0f},
	//};

	//Vertex list[] =
	//{
	//	{ position_list[0],texcoord_list[1] },
	//	{ position_list[1],texcoord_list[0] },
	//	{ position_list[2],texcoord_list[2] },
	//	{ position_list[3],texcoord_list[3] },


	//	{ position_list[4],texcoord_list[1] },
	//	{ position_list[5],texcoord_list[0] },
	//	{ position_list[6],texcoord_list[2] },
	//	{ position_list[7],texcoord_list[3] },


	//	{ position_list[1],texcoord_list[1] },
	//	{ position_list[6],texcoord_list[0] },
	//	{ position_list[5],texcoord_list[2] },
	//	{ position_list[2],texcoord_list[3] },

	//	{ position_list[7],texcoord_list[1] },
	//	{ position_list[0],texcoord_list[0] },
	//	{ position_list[3],texcoord_list[2] },
	//	{ position_list[4],texcoord_list[3] },

	//	{ position_list[3],texcoord_list[1] },
	//	{ position_list[2],texcoord_list[0] },
	//	{ position_list[5],texcoord_list[2] },
	//	{ position_list[4],texcoord_list[3] },

	//	{ position_list[7],texcoord_list[1] },
	//	{ position_list[6],texcoord_list[0] },
	//	{ position_list[1],texcoord_list[2] },
	//	{ position_list[0],texcoord_list[3] }
	//};

	//unsigned int index_list[] =
	//{
	//	0,1,2, 
	//	2,3,0, 
	//	4,5,6,
	//	6,7,4,
	//	8,9,10,
	//	10,11,8,
	//	12,13,14,
	//	14,15,12,
	//	16,17,18,
	//	18,19,16,
	//	20,21,22,
	//	22,23,20

	//};
	//unsigned int index_list_size = (sizeof(*RtlpNumberOf(index_list)));
	//m_ib = g_pGraphics_engine->GetRenderer()->CreateIndexBuffer();
	//m_ib->Load(index_list, index_list_size);

	//m_vb = g_pGraphics_engine->GetRenderer()->CreateVertexBuffer();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	g_pGraphics_engine->GetRenderer()->CompileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = g_pGraphics_engine->GetRenderer()->CreateVertexShader(shader_byte_code, size_shader);
	//m_vb->Load(list, sizeof(Vertex), (sizeof(*RtlpNumberOf(list))), shader_byte_code, size_shader);
	g_pGraphics_engine->GetRenderer()->ReleaseCompiledShader();

	g_pGraphics_engine->GetRenderer()->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_ps = g_pGraphics_engine->GetRenderer()->CreatePixelShader(shader_byte_code, size_shader);
	g_pGraphics_engine->GetRenderer()->ReleaseCompiledShader();

	constant cbuffer = { };
	m_cb = g_pGraphics_engine->GetRenderer()->CreateConstantBuffer();
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
	g_pGraphics_engine->GetCamera()->UpdateViewMatrix();
	auto context = g_pGraphics_engine->GetRenderer()->GetImmediateDeviceContext();
	context->ClearRenderTargetView(m_swap_chain.get(), 0.0f, 0.3f, 0.4f, 1.0f);
	context->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);


	constant cbuffer{};
	cbuffer.m_world = DirectX::XMMatrixIdentity();
	cbuffer.m_view = g_pGraphics_engine->GetCamera()->GetViewMatrix();
	cbuffer.m_projection = DirectX::XMMatrixPerspectiveFovLH(1.57f, ((float)(rc.right - rc.left) / (float)(rc.bottom - rc.top)), 0.1f, 1000.0f);

	m_cb->Update(context, &cbuffer);

	context->SetConstantBuffer(m_vs.get(), m_cb.get());
	context->SetConstantBuffer(m_ps.get(), m_cb.get());

	context->SetTextureShaderResource(m_ps.get(), m_texture.get());
	context->SetTextureShaderResource(m_vs.get(), m_texture.get());
	context->SetSamplerState(m_ps.get(), m_texture.get());
	context->SetSamplerState(m_vs.get(), m_texture.get());

	context->SetVertexShader(m_vs.get());
	context->SetPixelShader(m_ps.get());
	context->SetVertexBuffer(m_mesh->GetVertexBuffer());
	context->SetIndexBuffer(m_mesh->GetIndexBuffer());
	context->DrawIndexedTriangleList(m_mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);

	m_swap_chain->Present(true);

	m_old_time = m_new_time;
	m_new_time = GetTickCount64();

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
	g_pGraphics_engine->GetCamera()->KeyControl(key, m_delta_time);
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
		g_pGraphics_engine->GetCamera()->MouseControl(mouse_position.x - center.x, mouse_position.y - center.y);
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

GameWindow::~GameWindow() = default;