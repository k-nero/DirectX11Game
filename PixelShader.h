#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class PixelShader
{
public:
	PixelShader(Renderer* renderer);
	~PixelShader();
	bool Initialize(const void* shader_byte_code, size_t byte_code_size);
	void Release();
public:
	ID3D11PixelShader* GetShader() const;
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps = nullptr;
	Renderer* m_renderer = nullptr;
};

