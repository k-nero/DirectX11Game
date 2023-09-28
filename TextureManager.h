#pragma once
#include "ResourceManager.h"
#include "Texture.h"
class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	std::shared_ptr<Texture> CreateTextureFromFile(const wchar_t* file_path);
protected:
	Resource* CreateResourceFromFileConcrete(const wchar_t* file_path) override;
};

