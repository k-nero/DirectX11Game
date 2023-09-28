#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
}

void GraphicsEngine::Initialize()
{
	m_renderer = std::make_unique<Renderer>();
	m_renderer->Initialize();
	m_texture_manager = std::make_unique<TextureManager>();
	m_camera = std::make_unique<Camera>(Camera({ 0, 0, 2 }, { 0, 1, 0 }, -90.0f, 0.0f, 1.0f, 0.2f));
}

void GraphicsEngine::Shutdown()
{
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

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
