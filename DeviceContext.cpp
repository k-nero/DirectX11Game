#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext):m_deviceContext(deviceContext)
{

}

void DeviceContext::ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = { red, green, blue, alpha };
	m_deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
	m_deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	unsigned int stride = vertexBuffer->GetVertexSize();
	auto buffer = vertexBuffer->GetBuffer();
	auto layout = vertexBuffer->GetLayout();
	unsigned offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	m_deviceContext->IASetInputLayout(layout);
}

void DeviceContext::DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::SetViewportSize(unsigned width, unsigned height)
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (float)width;
	viewport.Height = (float)height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_deviceContext->RSSetViewports(1, &viewport);
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
