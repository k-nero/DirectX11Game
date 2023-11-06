#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class VertexShader
{
public:
	VertexShader(Renderer* renderer);
	void Release();
	~VertexShader();
	bool Initialize(const void* shader_byte_code, size_t byte_code_size);
public: 
	ID3D11VertexShader* GetShader();
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs = nullptr;
	Renderer* m_renderer = nullptr;
};

