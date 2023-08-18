#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext)
{
	m_deviceContext = deviceContext;
}

void DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = { red, green, blue, alpha };
	m_deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
}

void DeviceContext::Release()
{
	DeviceContext::~DeviceContext();
	delete this;
}

DeviceContext::~DeviceContext()
{
	if (m_deviceContext)
	{
		m_deviceContext->Release();
		m_deviceContext = nullptr;
	}
}
