#include "SwapChain.h"
#include "GraphicsEngine.h"
#include <iostream>

SwapChain::SwapChain()
{

}

bool SwapChain::Initialize(HWND hwnd, UINT width, UINT height, bool fullscreen)
{

	ID3D11Device* m_pDevice = GraphicsEngine::Get()->GetDevice();
	DXGI_SWAP_CHAIN_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 144;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = !fullscreen;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	__int64 hr = GraphicsEngine::Get()->GetDXGIFactory()->CreateSwapChain(m_pDevice, &desc, &m_swapChain);

	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* m_buffer = nullptr;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_buffer);
	if (FAILED(hr))
	{
		return false;
	}
	hr = m_pDevice->CreateRenderTargetView(m_buffer, nullptr, &m_rtv);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void SwapChain::Present(bool vsync)
{
	m_swapChain->Present(vsync, NULL);
}

ID3D11RenderTargetView* SwapChain::GetRenderTargetView()
{
	return m_rtv;
}

ID3D11DepthStencilView* SwapChain::GetDepthStencilView()
{
	return m_dsv;
}

void SwapChain::Release()
{
	SwapChain::~SwapChain();
	delete this;
}

SwapChain::~SwapChain()
{
	if (m_swapChain)
	{
		m_swapChain->Release();
		m_swapChain = nullptr;
	}
	if (m_rtv)
	{
		m_rtv->Release();
		m_rtv = nullptr;
	}

	if (m_dsv)
	{
		m_dsv->Release();
		m_dsv = nullptr;
	}
}
