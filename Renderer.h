#pragma once
#include <d3d11.h>
#include <memory>
#include <iostream>
#include <string>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"
#include "DomainShader.h"
#include "HullShader.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "Prerequisites.h"
#include "ReadCSO.h"

class Renderer
{
public:
	Renderer();
	[[deprecated("Use Renderer::Renderer() instead")]]
	bool Initialize();
	[[deprecated("Use Smart Pointer instead")]]
	void Shutdown();
	~Renderer();
public:
	ID3D11Device* GetDevice() const;
	IDXGIFactory* GetDXGIFactory();
	DeviceContext* GetImmediateDeviceContext() const;

	std::shared_ptr<SwapChain> CreateSwapChain();
	std::shared_ptr<IndexBuffer> CreateIndexBuffer();
	std::shared_ptr<VertexBuffer> CreateVertexBuffer();
	std::shared_ptr<ConstantBuffer> CreateConstantBuffer();
	void SetRasterizerState(bool is_front_culling);
public:
	std::shared_ptr<GeometryShader> CreateGeometryShader(const void* shader_byte_code, size_t byte_code_size);
	std::shared_ptr<DomainShader> CreateDomainShader(const void* shader_byte_code, size_t byte_code_size);
	std::shared_ptr<HullShader> CreateHullShader(const void* shader_byte_code, size_t byte_code_size);
	std::shared_ptr<PixelShader> CreatePixelShader(const void* shader_byte_code, size_t byte_code_size);
	std::shared_ptr<VertexShader> CreateVertexShader(const void* shader_byte_code, size_t byte_code_size);
	bool CompileGeometryShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompileDomainShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompileHullShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	void ReleaseCompiledShader();
private:
	void InitRasterizerState();
private:
	std::shared_ptr<DeviceContext> m_pDeviceContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIDevice> m_pDXGIDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> m_pDXGIAdapter = nullptr;
	Microsoft::WRL::ComPtr<IDXGIFactory> m_pDXGIFactory = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_pRasterizerState_backCulling = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_pRasterizerState_frontCulling = nullptr;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> m_blob = nullptr;
public:
	ID3D11InfoQueue* GetInfoQueue() const;
private:
	Microsoft::WRL::ComPtr<ID3D11Debug> m_debug = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InfoQueue> pInfoQueue = nullptr;
};
