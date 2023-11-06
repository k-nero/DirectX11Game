#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class PixelShader
{
public:
	PixelShader(Renderer* renderer);
	~PixelShader();
	HRESULT Initialize(const void* shader_byte_code, size_t byte_code_size);
	void Release();
public:
	ID3D11PixelShader* GetShader();
public:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;
	Renderer* m_renderer = nullptr;
};

