#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"

class VertexBuffer;
class VertexShader;
class PixelShader;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha) const;
	void SetVertexBuffer(VertexBuffer* vertexBuffer) const;
	void SetVertexShader(VertexShader* vertexShader) const;
	void SetPixelShader(PixelShader* pixelShader) const;
	void DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex) const;
	void DrawTriangleStrip(unsigned vertexCount, unsigned startVertexIndex) const;
	void SetViewportSize(unsigned width, unsigned height) const;
	void Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};

