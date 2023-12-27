#pragma once
#include "Prerequisites.h"
#include "Renderer.h"
#include "SwapChain.h"
#include "Texture.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetView(SwapChain* swapchain, float red, float green, float blue, float alpha) const;
	void SetIndexBuffer(IndexBuffer* indexBuffer) const;
	void SetVertexBuffer(VertexBuffer* vertexBuffer) const;
	void DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex) const;
	void DrawIndexedTriangleList(unsigned indexCount, unsigned startIndexLocation, unsigned startVertexLocation) const;
	void DrawTriangleStrip(unsigned vertexCount, unsigned startVertexIndex) const;
	void SetViewportSize(unsigned width, unsigned height) const;

	void SetVertexShaders(VertexShader* vertexShader) const;
	void SetPixelShaders(PixelShader* pixelShader) const;
	void SetGeometryShaders(GeometryShader* geometryShader) const;
	void SetHullShaders(HullShader* hullShader) const;
	void SetDomainShaders(DomainShader* domainShader) const;

	void SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer) const;
	void SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer) const;
	void SetConstantBuffer(GeometryShader* geometryShader, ConstantBuffer* buffer) const;
	void SetConstantBuffer(HullShader* hullShader, ConstantBuffer* buffer) const;
	void SetConstantBuffer(DomainShader* domainShader, ConstantBuffer* buffer) const;

	void SetTextureShaderResource(VertexShader* vertexShader, Texture* texture) const;
	void SetTextureShaderResource(PixelShader* pixelShader, Texture* texture) const;
	void SetTextureShaderResource(GeometryShader* geometryShader, Texture* texture) const;
	void SetTextureShaderResource(HullShader* hullShader, Texture* texture) const;
	void SetTextureShaderResource(DomainShader* domainShader, Texture* texture) const;

	void SetSamplerState(VertexShader* vertexShader, Texture* texture) const;
	void SetSamplerState(PixelShader* pixelShader, Texture* texture) const;
	void SetSamplerState(GeometryShader* geometryShader, Texture* texture) const;
	void SetSamplerState(HullShader* hullShader, Texture* texture) const;
	void SetSamplerState(DomainShader* domainShader, Texture* texture) const;

	void Release();
	~DeviceContext();
public:
	ID3D11DeviceContext* GetDeviceContext();
private:
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext = nullptr;
};

