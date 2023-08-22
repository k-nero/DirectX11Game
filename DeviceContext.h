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
	void ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetVertexShader(VertexShader* vertexShader);
	void SetPixelShader(PixelShader* pixelShader);
	void DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex);
	void DrawTriangleStrip(unsigned vertexCount, unsigned startVertexIndex);
	void SetViewportSize(unsigned width, unsigned height);
	void Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};

