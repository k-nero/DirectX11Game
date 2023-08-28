#pragma once
#include <d3d11.h>
#include <iostream>
#include <d3dcompiler.h>
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <wrl/client.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexShader;
class PixelShader;

class GraphicsEngine
{
public:
	GraphicsEngine();
	bool Initialize();
	void Shutdown();
	~GraphicsEngine();
public:
	ID3D11Device* GetDevice() const;
	IDXGIFactory* GetDXGIFactory();
	static GraphicsEngine* Get();
	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext() const;
	VertexBuffer* CreateVertexBuffer();

public:
	VertexShader* CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	PixelShader* CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);
	bool CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void ReleaseCompiledShader();
private:
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	DeviceContext* m_pDeviceContext = nullptr;

	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIDevice> m_pDXGIDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> m_pDXGIAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory> m_pDXGIFactory = nullptr;
private:
	Microsoft::WRL::ComPtr<ID3DBlob> m_blob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> m_vsblob = nullptr;
	Microsoft::WRL::ComPtr<ID3DBlob> m_psblob = nullptr;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs = nullptr;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps = nullptr;
public:
	ID3D11InfoQueue* GetInfoQueue() const;
private:
	Microsoft::WRL::ComPtr<ID3D11Debug> m_debug = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InfoQueue> pInfoQueue = nullptr;
};
