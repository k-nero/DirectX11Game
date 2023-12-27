#pragma once
#include <memory>
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "IInputListener.h"
#include "InputSystem.h"
#include "Camera.h"
#include "DataStructure.h"
#include "MeshManager.h"
#include "Mesh.h"

class GameWindow : public Window, public IInputListener
{
public: 
	GameWindow();
	void Render();
	void DrawMesh( Mesh* mesh,  VertexShader* vertexShader,  PixelShader* pixelShader,  ConstantBuffer* constantBuffer,  Texture* texture);
	void UpdateSkyBoxAtt();
	void UpdateModelAtt();
	~GameWindow();

	// Inherited via Window
	void OnCreate() override;
	void OnDestroy() override;
	void OnUpdate() override;
	void OnFocus() override;
	void OnUnFocus() override;
	void OnResize() override;
	// Inherited via IInputListener
	void OnKeyDown(int key) override;
	void OnKeyUp(int key) override;
	void OnMouseMove(const DirectX::XMFLOAT2& mouse_position) override;
	void OnRightMouseDown(const DirectX::XMFLOAT2& mouse_position) override;
	void OnRightMouseUp(const DirectX::XMFLOAT2& mouse_position) override;
	void OnLeftMouseDown(const DirectX::XMFLOAT2& mouse_position) override;
	void OnLeftMouseUp(const DirectX::XMFLOAT2& mouse_position) override;
private:
	GraphicsEngine* g_pGraphics_engine = nullptr;
private:
	std::shared_ptr<SwapChain> m_swap_chain = nullptr;
	std::shared_ptr<VertexBuffer> m_vb = nullptr;
	std::shared_ptr<VertexShader> m_vs = nullptr;
	std::shared_ptr<PixelShader> m_ps = nullptr;
	std::shared_ptr<PixelShader> m_sky_ps = nullptr;
	std::shared_ptr<GeometryShader> m_gs = nullptr;
	std::shared_ptr<DomainShader> m_ds = nullptr;
	std::shared_ptr<HullShader> m_hs = nullptr;
	std::shared_ptr<ConstantBuffer> m_cb = nullptr;
	std::shared_ptr<ConstantBuffer> m_sky_cb = nullptr;
	std::shared_ptr<IndexBuffer> m_ib = nullptr;
	std::shared_ptr<Texture> m_texture = nullptr;
	std::shared_ptr<Mesh> m_mesh = nullptr;
	std::shared_ptr<Mesh> m_sky_box = nullptr;
	std::shared_ptr<Texture> m_sky_tex = nullptr;
private:
	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	ULONG64 m_old_time = 0;
	ULONG64 m_new_time = 0;
	float m_delta_time = 0.0f;

	DirectX::XMVECTOR camera_pos{ 0.0f, 0.0f, -2.0f };
	bool m_play_state = true;
	bool m_fullscreen_state = false;


    DirectX::XMMATRIX m_world_matrix;
	DirectX::XMMATRIX m_view_matrix;
	DirectX::XMMATRIX m_proj_matrix;
};