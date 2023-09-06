#include "VertexShader.h"

VertexShader::VertexShader() = default;

void VertexShader::Release()
{
   VertexShader::~VertexShader();
   delete this;
}

VertexShader::~VertexShader() = default;

bool VertexShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
	const auto hr = GraphicsEngine::Get()->GetDevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs);
    return hr >= 0x0L ? true : false;
}

ID3D11VertexShader* VertexShader::GetShader() const
{
    return m_vs.Get();
}
