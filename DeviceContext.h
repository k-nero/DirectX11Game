#pragma once
#include <d3d11.h>
#include "GraphicsEngine.h"
#include "VertexBuffer.h"

class VertexBuffer;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetView(ID3D11RenderTargetView* renderTargetView, float red, float green, float blue, float alpha);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void DrawTriangleList(unsigned vertexCount, unsigned startVertexIndex);
	void SetViewportSize(unsigned width, unsigned height);
	void Release();
	~DeviceContext();
private:
	ID3D11DeviceContext* m_deviceContext = nullptr;
};

