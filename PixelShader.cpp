#include "PixelShader.h"

PixelShader::PixelShader(Renderer* renderer) : m_renderer(renderer)
{
   
}

PixelShader::~PixelShader()
{

}

HRESULT PixelShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
    HRESULT hr = m_renderer->GetDevice()->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, m_ps.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
		throw std::exception("PixelShader not created successfully");
	}
    return hr;
}

void PixelShader::Release()
{
    delete this;
}

ID3D11PixelShader* PixelShader::GetShader() const
{
    return m_ps.Get();
}
