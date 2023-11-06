#pragma once
#include "Renderer.h"
#include "Prerequisites.h"

class SwapChain
{
public:
	SwapChain(Renderer* renderer);
	bool Initialize(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen);
	void Present(bool vsync);
	ID3D11RenderTargetView* GetRenderTargetView() const;
	ID3D11DepthStencilView* GetDepthStencilView() const;
	/// <summary>
	/// Derecated 
	/// Use ComPtr instead
	/// </summary>
	void Release();
	void ReloadBuffers(unsigned int width, unsigned int height);
	void Resize(unsigned int width, unsigned int height);
	void SetFullScreen(unsigned int width, unsigned int height, bool fullscreen);
	~SwapChain();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_dsv = nullptr;
	Renderer* m_renderer = nullptr;
};

