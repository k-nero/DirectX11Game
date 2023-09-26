#include "SwapChain.h"
#include <wrl/client.h>

SwapChain::SwapChain() = default;

bool SwapChain::Initialize(HWND hwnd, unsigned int width, unsigned int height, bool fullscreen)
{

	Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice = GraphicsEngine::Get()->GetDevice();
	DXGI_SWAP_CHAIN_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.BufferCount = 2;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 144;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferUsage = 0x00000020UL;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 4;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = !fullscreen;
	desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	__int64 hr = GraphicsEngine::Get()->GetDXGIFactory()->CreateSwapChain(m_pDevice.Get(), &desc, &m_swapChain);

	if (hr < 0x0L)
	{
		return false;
	}

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_buffer = nullptr;
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_buffer);
	if (hr < 0x0L)
	{
		return false;
	}

	hr = m_pDevice->CreateRenderTargetView(m_buffer.Get(), nullptr, &m_rtv);

	if (hr < 0x0L)
	{
		return false;
	}
	return true;
}

void SwapChain::Present(bool vsync)
{
	m_swapChain->Present(vsync, NULL);
}

ID3D11RenderTargetView* SwapChain::GetRenderTargetView() const
{
	return m_rtv.Get();
}

ID3D11DepthStencilView* SwapChain::GetDepthStencilView() const
{
	return m_dsv.Get();
}

void SwapChain::Release()
{
	SwapChain::~SwapChain();
	delete this;
}

SwapChain::~SwapChain() = default;
