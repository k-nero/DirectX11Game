#include "Texture.h"

Texture::Texture(const wchar_t* full_path) : Resource(full_path)
{
	DirectX::TexMetadata metadata;
	DirectX::ScratchImage image;
	HRESULT rs = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, &metadata, image);
	if ((HRESULT)rs < 0)
	{
		throw std::exception("Texture not found");
	}
	rs = DirectX::CreateTexture(GraphicsEngine::Get()->GetRenderer()->GetDevice(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &m_texture);
	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
	desc.Format = metadata.format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = (UINT)metadata.mipLevels;
	desc.Texture2D.MostDetailedMip = 0;
	GraphicsEngine::Get()->GetRenderer()->GetDevice()->CreateShaderResourceView(m_texture.Get(), NULL, &m_texture_view);

	D3D11_SAMPLER_DESC  sampler_desc = {};
	memset((&sampler_desc), 0, (sizeof(D3D11_SAMPLER_DESC)));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sampler_desc.MipLODBias = 0.0f;
	sampler_desc.MaxAnisotropy = 1;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampler_desc.MinLOD = -FLT_MAX;
	sampler_desc.MaxLOD = FLT_MAX;

	GraphicsEngine::Get()->GetRenderer()->GetDevice()->CreateSamplerState(&sampler_desc, &m_sampler_state);
}

Texture::~Texture()
{
}

ID3D11ShaderResourceView* Texture::GetTextureResourceView()
{
	return this->m_texture_view.Get();
}

ID3D11SamplerState* Texture::GetSamplerState()
{
	return this->m_sampler_state.Get();
}
