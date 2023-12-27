#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class GeometryShader
{
public:
	GeometryShader(Renderer* renderer);
	~GeometryShader();
	HRESULT Initialize(const void* shader_byte_code, size_t byte_code_size);
public:
	ID3D11GeometryShader* GetShader() const;
private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;
	Renderer* m_renderer = nullptr;
};

