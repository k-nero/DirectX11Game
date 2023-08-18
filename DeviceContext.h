#pragma once
#include <d3d11.h>

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha);
	void Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};

