#include "PixelShader.h"

PixelShader::PixelShader(Renderer* renderer) : m_renderer(renderer)
{
   
}

PixelShader::~PixelShader()
{

}

bool PixelShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
    HRESULT hr = m_renderer->GetDevice()->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps);
    return hr >= 0x0L ? true : false;
}

void PixelShader::Release()
{
    delete this;
}

ID3D11PixelShader* PixelShader::GetShader() const
{
    return this->m_ps.Get();
}
