#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class ConstantBuffer
{
public:
	ConstantBuffer(Renderer * renderer);
	bool Load(void* buffer, unsigned size);
	void Update(DeviceContext* deviceContext, void* buffer);
	void Release();
	~ConstantBuffer();
public:
	ID3D11Buffer* GetBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	Renderer* m_renderer = nullptr;
};

