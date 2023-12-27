#include "GeometryShader.h"

GeometryShader::GeometryShader(Renderer* renderer)
{
}

GeometryShader::~GeometryShader()
{
}

HRESULT GeometryShader::Initialize(const void* shader_byte_code, size_t byte_code_size)
{
	HRESULT hr = m_renderer->GetDevice()->CreateGeometryShader(shader_byte_code, byte_code_size, nullptr, m_gs.GetAddressOf());
	if (FAILED(hr))
	{
		throw std::exception("GeometryShader not created successfully");
	}
	return hr;
}

ID3D11GeometryShader* GeometryShader::GetShader() const
{
	return m_gs.Get();
}
