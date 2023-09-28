#pragma once
#include "Resource.h"
#include "GraphicsEngine.h"

class Texture : public Resource
{
public:
	Texture(const wchar_t* full_path);
	~Texture();
public:
	ID3D11ShaderResourceView* GetTextureResourceView();
private:
	Microsoft::WRL::ComPtr<ID3D11Resource> m_texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture_view;
};

