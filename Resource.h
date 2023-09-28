#pragma once
#include <string>
#include <exception>
#include <DirectXTex.h>
class Resource
{
public:
	Resource(const wchar_t* full_path);
	virtual ~Resource();
protected:
	std::wstring m_resource_path;
};

