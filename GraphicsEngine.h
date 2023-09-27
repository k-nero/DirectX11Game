#pragma once
#include "Renderer.h"
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
public:
	static GraphicsEngine* Get();
private:
	std::shared_ptr<Renderer> m_renderer = nullptr;
	static GraphicsEngine* m_engine;
};
