#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
	m_renderer = std::make_unique<Renderer>();
	m_renderer->Initialize();
	m_texture_manager = std::make_unique<TextureManager>();
	m_camera = std::make_unique<Camera>(Camera({ 0, 0, 2 }, { 0, 1, 0 }, -90.0f, 0.0f, 1.0f, 0.2f));
	m_mesh_manager = std::make_unique<MeshManager>();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	m_renderer->CompileVertexShader(L"VetexMeshLayoutShader.hlsl", "main", &shader_byte_code, &size_shader);
	m_mesh_layout_byte_code = new unsigned char[size_shader];
	memcpy(m_mesh_layout_byte_code, shader_byte_code, size_shader);
	m_mesh_layout_size = size_shader;
	m_renderer->ReleaseCompiledShader();
}

void GraphicsEngine::Shutdown()
{
	delete[] m_mesh_layout_byte_code;
}

GraphicsEngine::~GraphicsEngine()
{
}

Renderer* GraphicsEngine::GetRenderer()
{
	return m_renderer.get();
}

TextureManager* GraphicsEngine::GetTextureManager()
{
	return m_texture_manager.get();
}

Camera* GraphicsEngine::GetCamera()
{
	return m_camera.get();
}

MeshManager* GraphicsEngine::GetMeshManager()
{
	return this->m_mesh_manager.get();
}

void GraphicsEngine::GetVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
