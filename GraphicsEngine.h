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
public:
	static GraphicsEngine* Get();
private:
	std::unique_ptr<Renderer> m_renderer = nullptr;
	std::unique_ptr<TextureManager> m_texture_manager = nullptr;
	std::unique_ptr<Camera> m_camera = nullptr;

	static GraphicsEngine* m_engine;
};
