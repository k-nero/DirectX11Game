#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class HullShader
{
public:
	HullShader(Renderer* renderer);
	~HullShader();
	HRESULT Initialize(const void* shader_byte_code, size_t byte_code_size);
public:
	ID3D11HullShader* GetShader();
private:
	Renderer* m_renderer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_hs;
};

