#pragma once
#include "GraphicsEngine.h"

class PixelShader
{
public:
	PixelShader();
	~PixelShader();
	bool Initialize(const void* shader_byte_code, size_t byte_code_size);
	void Release();
public:
	ID3D11PixelShader* GetShader() const;
private:
	ID3D11PixelShader* m_ps = nullptr;
};

