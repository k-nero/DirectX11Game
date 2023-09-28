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
}

Texture::~Texture()
{
}

ID3D11ShaderResourceView* Texture::GetTextureResourceView()
{
	return this->m_texture_view.Get();
}
