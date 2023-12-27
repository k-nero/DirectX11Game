#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class DomainShader
{
public:
	DomainShader(Renderer* renderer);
	~DomainShader();
	HRESULT Initialize(const void* shader_byte_code, size_t byte_code_size);
public:
	ID3D11DomainShader* GetShader();
private:
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_ds;
	Renderer* m_renderer = nullptr;
};

