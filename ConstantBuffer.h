#pragma once
#include <wrl/client.h>
#include <d3d11.h>
#include "DeviceContext.h"

class DeviceContext;

class ConstantBuffer
{
public:
	ConstantBuffer();
	bool Load(void* buffer, unsigned size);
	void Update(DeviceContext* deviceContext, void* buffer);
	void Release();
	~ConstantBuffer();
public:
	ID3D11Buffer* GetBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
};

