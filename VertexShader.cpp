#include "VertexShader.h"

VertexShader::VertexShader()
{
}

void VertexShader::Release()
{
   if (m_vs)m_vs->Release();
   m_vs = nullptr;
   delete this;
}

VertexShader::~VertexShader()
{
    if (m_vs)m_vs->Release();
}

bool VertexShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
    if (!SUCCEEDED(GraphicsEngine::Get()->GetDevice()->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
    {
		return false;
	}

    return true;
}

ID3D11VertexShader* VertexShader::GetShader()
{
    return this->m_vs;
}
