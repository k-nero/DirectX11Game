#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include "GraphicsEngine.h"

class IndexBuffer
{
public:
	IndexBuffer();
	bool Load(void* list_indices, UINT size_list);
	unsigned int GetIndexListSize() const;
	void Release();
	~IndexBuffer();
public:
	ID3D11Buffer* GetBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	unsigned int m_size_list = 0;
};

