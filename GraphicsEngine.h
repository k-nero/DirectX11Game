#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Prerequisites.h"

class GraphicsEngine
{
public:
	GraphicsEngine();
	void Initialize();
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

	unsigned char* m_mesh_layout_byte_code = nullptr;
	size_t m_mesh_layout_size = 0;
};
