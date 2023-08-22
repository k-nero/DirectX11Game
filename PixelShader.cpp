#include "PixelShader.h"

PixelShader::PixelShader()
{
}

PixelShader::~PixelShader()
{
    if (m_ps)m_ps->Release();
}

bool PixelShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
    HRESULT hr = GraphicsEngine::Get()->GetDevice()->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps);
    if (FAILED(hr))
    {  
		return false;
	}
    return true;
}

void PixelShader::Release()
{

    if (m_ps)m_ps->Release();
    m_ps = nullptr;
    delete this;
}

ID3D11PixelShader* PixelShader::GetShader()
{
    return this->m_ps;
}
