#pragma once
#include <unordered_map>
#include <memory>
#include "Resource.h"
#include <filesystem>

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	std::shared_ptr<Resource> CreateResourceFromFile(const wchar_t* file_path);
protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* file_path) = 0;
private:
	std::unordered_map<std::wstring, std::shared_ptr<Resource>> m_resource_map;
};

