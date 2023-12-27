#include "DomainShader.h"

DomainShader::DomainShader(Renderer* renderer)
{
}

DomainShader::~DomainShader()
{
}

HRESULT DomainShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = m_renderer->GetDevice()->CreateDomainShader(shader_byte_code, byte_code_size, nullptr, m_ds.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		throw std::exception("DomainShader not created successfully");
	}
	return hr;
}

ID3D11DomainShader* DomainShader::GetShader()
{
	return m_ds.Get();
}
