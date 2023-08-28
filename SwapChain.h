#pragma once
#include "GraphicsEngine.h"
#include <wrl/client.h>

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
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_dsv = nullptr;
};

