#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{

}

std::shared_ptr<Resource> ResourceManager::CreateResourceFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::filesystem::absolute(file_path);
	auto it = m_resource_map.find(full_path);
	if (it != m_resource_map.end())
	{
		return it->second;
	}
	auto resource = CreateResourceFromFileConcrete(full_path.c_str());
	if (resource)
	{
		m_resource_map[full_path] = std::shared_ptr<Resource>(resource);
		return m_resource_map[full_path];
	}
	delete[] file_path;
	return nullptr;
}
