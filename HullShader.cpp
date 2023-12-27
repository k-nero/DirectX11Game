#include "HullShader.h"

HullShader::HullShader(Renderer* renderer)
{
}

HullShader::~HullShader()
{
}

HRESULT HullShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = m_renderer->GetDevice()->CreateHullShader(shader_byte_code, byte_code_size, nullptr, m_hs.ReleaseAndGetAddressOf());
	if (FAILED(hr))
	{
		throw std::exception("HullShader not created successfully");
	}
	return hr;
}

ID3D11HullShader* HullShader::GetShader()
{
	return m_hs.Get();
}
