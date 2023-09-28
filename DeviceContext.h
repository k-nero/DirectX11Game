#pragma once
#include "Prerequisites.h"
#include "Renderer.h"
#include "Texture.h"
class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha) const;
	void SetIndexBuffer(IndexBuffer* indexBuffer) const;
	void SetVertexBuffer(VertexBuffer* vertexBuffer) const;
	void SetVertexShader(VertexShader* vertexShader) const;
	void SetPixelShader(PixelShader* pixelShader) const;
	void DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex) const;
	void DrawIndexedTriangleList(unsigned indexCount, unsigned startIndexLocation, unsigned startVertexLocation) const;
	void DrawTriangleStrip(unsigned vertexCount, unsigned startVertexIndex) const;
	void SetViewportSize(unsigned width, unsigned height) const;
	void SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer) const;
	void SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer) const;
	void SetTexture(VertexShader* vertexShader, Texture* texture) const;
	void SetTexture(PixelShader* pixelShader, Texture* texture) const;
	void Release();
	~DeviceContext();
public:
	ID3D11DeviceContext* GetDeviceContext();
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;
};

