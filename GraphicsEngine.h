#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;

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
	VertexBuffer* CreateVertexBuffer();
	void CreateShaders();
	void SetShaders();
	void GetShaderBufferAndSize(void** byteCode, unsigned* size);
private:
	ID3D11Device* m_pDevice = nullptr;
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

	DeviceContext* m_pDeviceContext = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGIDevice* m_pDXGIDevice = nullptr;
	IDXGIAdapter* m_pDXGIAdapter = nullptr;
	IDXGIFactory* m_pDXGIFactory = nullptr;
private:
	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;
};
