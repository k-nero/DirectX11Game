#pragma once
#include "GraphicsEngine.h"

class VertexShader
{
public:
	VertexShader();
	void Release();
	~VertexShader();
	bool Initialize(const void* shader_byte_code, size_t byte_code_size);
public: 
	ID3D11VertexShader* GetShader() const;
private:
	ID3D11VertexShader* m_vs = nullptr;

};

