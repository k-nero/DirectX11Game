#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "Prerequisites.h"
#include "Constant.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	void Shutdown();
	~GraphicsEngine();
public:
	Renderer* GetRenderer();
	TextureManager* GetTextureManager();
	Camera* GetCamera();
	MeshManager* GetMeshManager();
	void GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);
public:
	static GraphicsEngine* Get();
private:
	std::unique_ptr<Renderer> m_renderer = nullptr;
	std::unique_ptr<TextureManager> m_texture_manager = nullptr;
	std::unique_ptr<Camera> m_camera = nullptr;
	std::unique_ptr<MeshManager> m_mesh_manager = nullptr;
	static GraphicsEngine* m_engine;

	void* m_mesh_layout_byte_code;
	size_t m_mesh_layout_size = 0;
};
