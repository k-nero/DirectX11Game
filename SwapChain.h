#pragma once
#include "GraphicsEngine.h"

class SwapChain
{
public:
	SwapChain();
	bool Initialize(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen);
	void Present(bool vsync);
	ID3D11RenderTargetView* GetRenderTargetView() const;
	ID3D11DepthStencilView* GetDepthStencilView() const;
	void Release();
	~SwapChain();
private:
	IDXGISwapChain* m_swapChain = nullptr;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11DepthStencilView* m_dsv = nullptr;
};

