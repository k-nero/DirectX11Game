#include "VertexShader.h"

VertexShader::VertexShader(Renderer* renderer) : m_renderer(renderer)
{
}

void VertexShader::Release()
{
   VertexShader::~VertexShader();
   delete this;
}

bool VertexShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
	auto hr = m_renderer->GetDevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, m_vs.ReleaseAndGetAddressOf());
    return hr >= 0x0L ? true : false;
}

ID3D11VertexShader* VertexShader::GetShader() 
{
    return m_vs.Get();
}

VertexShader::~VertexShader() = default;

