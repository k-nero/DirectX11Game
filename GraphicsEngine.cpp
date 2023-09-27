#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{
}

void GraphicsEngine::Initialize()
{
	m_renderer = std::make_shared<Renderer>();
	m_renderer->Initialize();
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

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
