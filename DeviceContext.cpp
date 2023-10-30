#include "DeviceContext.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) : m_deviceContext(deviceContext)
{
}

void DeviceContext::ClearRenderTargetView(SwapChain* swapchain, float red, float green, float blue, float alpha) const
{
	FLOAT clearColor[] = { red, green, blue, alpha };
	auto renderTargetView = swapchain->GetRenderTargetView();
	auto depthStencilView = swapchain->GetDepthStencilView();
	m_deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
	m_deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	m_deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
}

void DeviceContext::SetIndexBuffer(IndexBuffer* indexBuffer) const
{
	m_deviceContext->IASetIndexBuffer(indexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::SetVertexBuffer(VertexBuffer* vertexBuffer) const
{
	unsigned int stride = vertexBuffer->GetVertexSize();
	auto buffer = vertexBuffer->GetBuffer();
	auto layout = vertexBuffer->GetLayout();
	unsigned offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
	m_deviceContext->IASetInputLayout(layout);
}

void DeviceContext::SetVertexShader(VertexShader* vertexShader) const
{
	m_deviceContext->VSSetShader(vertexShader->GetShader(), nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixelShader) const
{
	m_deviceContext->PSSetShader(pixelShader->GetShader(), nullptr, 0);
}

void DeviceContext::DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex) const
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::DrawIndexedTriangleList(unsigned indexCount, unsigned startIndexLocation, unsigned startVertexLocation) const
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->DrawIndexed(indexCount, startIndexLocation, startVertexLocation);
}

void DeviceContext::DrawTriangleStrip(unsigned vertexCount, unsigned startVertexIndex) const
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_deviceContext->Draw(vertexCount, startVertexIndex);
}

void DeviceContext::SetViewportSize(unsigned width, unsigned height) const
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	m_deviceContext->RSSetViewports(1, &viewport);
}

void DeviceContext::SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer) const
{
	vertexShader;
	ID3D11Buffer* bufferPtr = buffer->GetBuffer();
	m_deviceContext->VSSetConstantBuffers(0, 1, &bufferPtr);
}

void DeviceContext::SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer) const
{
	ID3D11Buffer* bufferPtr = buffer->GetBuffer();
	m_deviceContext->PSSetConstantBuffers(0, 1, &bufferPtr);
}

void DeviceContext::SetTextureShaderResource(VertexShader* vertexShader, Texture* texture) const
{
	ID3D11ShaderResourceView* resourceView = texture->GetTextureResourceView();
	m_deviceContext->VSSetShaderResources(0, 1, &resourceView);
}

void DeviceContext::SetTextureShaderResource(PixelShader* pixelShader, Texture* texture) const
{
	ID3D11ShaderResourceView* resourceView = texture->GetTextureResourceView();
	m_deviceContext->PSSetShaderResources(0, 1, &resourceView);
}

void DeviceContext::SetSamplerState(VertexShader* vertexShader, Texture* texture) const
{
	ID3D11SamplerState* sampler_state = texture->GetSamplerState();
	m_deviceContext->VSSetSamplers(0, 1, &sampler_state);
}

void DeviceContext::SetSamplerState(PixelShader* pixelShader, Texture* texture) const
{
	ID3D11SamplerState* sampler_state = texture->GetSamplerState();
	m_deviceContext->PSSetSamplers(0, 1, &sampler_state);
}

void DeviceContext::Release()
{
	DeviceContext::~DeviceContext();
	delete this;
}

DeviceContext::~DeviceContext()
{
	
}

ID3D11DeviceContext* DeviceContext::GetDeviceContext()
{
	return this->m_deviceContext.Get();
}
