#include "GameWindow.h"

using namespace DirectX;

GameWindow::GameWindow() = default;

void GameWindow::Render()
{
	RECT rc = this->GetClient();
	g_pGraphics_engine->GetCamera()->UpdateViewMatrix();
	auto context = g_pGraphics_engine->GetRenderer()->GetImmediateDeviceContext();
	context->ClearRenderTargetView(m_swap_chain.get(), 0.0f, 0.3f, 0.4f, 1.0f);
	context->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	m_world_matrix = DirectX::XMMatrixIdentity();
	m_view_matrix = g_pGraphics_engine->GetCamera()->GetViewMatrix();
	m_proj_matrix = DirectX::XMMatrixPerspectiveFovLH(1.57f, ((float)(rc.right - rc.left) / (float)(rc.bottom - rc.top)), 0.1f, 1000.0f);

	g_pGraphics_engine->GetRenderer()->SetRasterizerState(true);
	UpdateModelAtt();
	DrawMesh(m_mesh.get(), m_vs.get(), m_ps.get(), m_cb.get(), m_texture.get());

	g_pGraphics_engine->GetRenderer()->SetRasterizerState(false);
	UpdateSkyBoxAtt();
	DrawMesh(m_sky_box.get(), m_vs.get(), m_sky_ps.get(), m_sky_cb.get(), m_sky_tex.get());

	m_swap_chain->Present(true);

	m_old_time = m_new_time;
	m_new_time = GetTickCount64();
	m_delta_time = (m_old_time) ? ((m_new_time - m_old_time) / 100.0f) : 0;
}

void GameWindow::DrawMesh( Mesh* mesh,  VertexShader* vertexShader,  PixelShader* pixelShader,  ConstantBuffer* constantBuffer,  Texture* texture)
{
	auto context = g_pGraphics_engine->GetRenderer()->GetImmediateDeviceContext();
	context->SetConstantBuffer(vertexShader, constantBuffer);
	context->SetConstantBuffer(pixelShader, constantBuffer);

	if (texture != nullptr)
	{
		context->SetTextureShaderResource(pixelShader, texture);
		context->SetTextureShaderResource(vertexShader, texture);
		context->SetSamplerState(pixelShader, texture);
		context->SetSamplerState(vertexShader, texture);
	}
	
	context->SetVertexShader(vertexShader);
	context->SetPixelShader(pixelShader);
	context->SetVertexBuffer(mesh->GetVertexBuffer());
	context->SetIndexBuffer(mesh->GetIndexBuffer());
	context->DrawIndexedTriangleList(mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
}

void GameWindow::UpdateSkyBoxAtt()
{
	constant cb{};

	cb.m_world = DirectX::XMMatrixScalingFromVector({ 1000.0f, 1000.0f, 1000.0f }) * DirectX::XMMatrixTranslationFromVector(g_pGraphics_engine->GetCamera()->GetCameraPosition()) ;
	cb.m_view = m_view_matrix;
	cb.m_projection = m_proj_matrix;

	m_sky_cb->Update(GraphicsEngine::Get()->GetRenderer()->GetImmediateDeviceContext(), &cb);
}

void GameWindow::UpdateModelAtt()
{
	constant cb{};
	cb.m_world = m_world_matrix;
	cb.m_view = m_view_matrix;
	cb.m_projection = m_proj_matrix;
	cb.m_light_direction = { 0.0f, 0.0f, -1.0f, 0.0f };
	DirectX::XMStoreFloat4(&cb.camera_position, g_pGraphics_engine->GetCamera()->GetCameraPosition());
	m_cb->Update(GraphicsEngine::Get()->GetRenderer()->GetImmediateDeviceContext(), &cb);
}

void GameWindow::OnCreate()
{
	Window::OnCreate();
	InputSystem::Get()->AddListener(this);
	InputSystem::Get()->ShowCursor(false);
	InputSystem::Get()->ShowCursor(!m_play_state);
	g_pGraphics_engine = GraphicsEngine::Get();

	m_texture = g_pGraphics_engine->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
	m_sky_tex = g_pGraphics_engine->GetTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\sky.jpg");

	m_mesh = g_pGraphics_engine->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj");
	m_sky_box = g_pGraphics_engine->GetMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\sphere_hq.obj");

	m_swap_chain = g_pGraphics_engine->GetRenderer()->CreateSwapChain();
	auto client = this->GetClient();
	m_swap_chain->Initialize(this->m_hWnd, client.right - client.left, client.bottom - client.top, false);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	g_pGraphics_engine->GetRenderer()->CompileVertexShader(L"VertexShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_vs = g_pGraphics_engine->GetRenderer()->CreateVertexShader(shader_byte_code, size_shader);
	g_pGraphics_engine->GetRenderer()->ReleaseCompiledShader();

	g_pGraphics_engine->GetRenderer()->CompilePixelShader(L"PixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_ps = g_pGraphics_engine->GetRenderer()->CreatePixelShader(shader_byte_code, size_shader);
	g_pGraphics_engine->GetRenderer()->ReleaseCompiledShader();

	g_pGraphics_engine->GetRenderer()->CompilePixelShader(L"SkyboxPixelShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_sky_ps = g_pGraphics_engine->GetRenderer()->CreatePixelShader(shader_byte_code, size_shader);
	g_pGraphics_engine->GetRenderer()->ReleaseCompiledShader();

	constant cbuffer = { };
	m_cb = g_pGraphics_engine->GetRenderer()->CreateConstantBuffer();
	m_cb->Load(&cbuffer, sizeof(constant));
	m_sky_cb = g_pGraphics_engine->GetRenderer()->CreateConstantBuffer();
	m_sky_cb->Load(&cbuffer, sizeof(constant));
}

void GameWindow::OnDestroy()
{
	//m_swap_chain->SetFullScreen(false, 1280, 720);
	Window::OnDestroy();
	g_pGraphics_engine->Shutdown();
}



void GameWindow::OnUpdate()
{
	Window::OnUpdate();
	InputSystem::Get()->Update();
	Render();
}

void GameWindow::OnFocus()
{
	InputSystem::Get()->AddListener(this);
}

void GameWindow::OnUnFocus()
{
	InputSystem::Get()->RemoveListener(this);
}

void GameWindow::OnResize()
{
	RECT rc = this->GetClient();
	if (rc.right <= 0 || rc.bottom <= 0)
	{
		return;
	}
	m_swap_chain->Resize(rc.right, rc.bottom);
	Render();
}

void GameWindow::OnKeyDown(int key)
{
	g_pGraphics_engine->GetCamera()->KeyControl(key, m_delta_time);
	if (key == VK_ESCAPE)
	{
		this->m_play_state = !this->m_play_state;
		InputSystem::Get()->ShowCursor(!this->m_play_state);
	}
	if (key == VK_F11)
	{
		m_fullscreen_state = !m_fullscreen_state;
		RECT rc = this->GetPhysicalScreensize();
		m_swap_chain->SetFullScreen(rc.right, rc.bottom, m_fullscreen_state);
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