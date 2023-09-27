#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class IndexBuffer
{
public:
	IndexBuffer(Renderer* renderer);
	bool Load(void* list_indices, UINT size_list);
	unsigned int GetIndexListSize() const;
	void Release();
	~IndexBuffer();
public:
	ID3D11Buffer* GetBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	unsigned int m_size_list = 0;
	Renderer* m_renderer = nullptr;
};

