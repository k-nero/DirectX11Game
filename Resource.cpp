#include "Resource.h"

Resource::Resource(const wchar_t* full_path)
{
	m_resource_path = full_path;
}

Resource::~Resource()
{
	m_resource_path.clear();
}
