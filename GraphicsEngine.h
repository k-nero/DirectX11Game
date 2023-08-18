#pragma once
#include <d3d11.h>
#include "SwapChain.h"
#include "DeviceContext.h"

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool Initialize();
	void Shutdown();
	~GraphicsEngine();
public:
	ID3D11Device* GetDevice();
	//ID3D11DeviceContext* GetDeviceContext();
	IDXGIFactory* GetDXGIFactory();
	static GraphicsEngine* Get();
	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
private:
	ID3D11Device* m_pDevice = nullptr;
	D3D_FEATURE_LEVEL m_featureLevel;

	DeviceContext* m_pDeviceContext = nullptr;

	IDXGIDevice* m_pDXGIDevice = nullptr;
	IDXGIAdapter* m_pDXGIAdapter = nullptr;
	IDXGIFactory* m_pDXGIFactory = nullptr;
private:
	friend class SwapChain;
};
