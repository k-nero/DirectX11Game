#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
{

}

bool GraphicsEngine::Initialize()
{
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE
	};

	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_0
	};

	HRESULT hr;
	ID3D11DeviceContext* deviceContext = nullptr;
	for (UINT driverTypeIndex = 0; driverTypeIndex < ARRAYSIZE(driverTypes); driverTypeIndex++)
	{
		auto m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(NULL, m_driverType, NULL, NULL, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_pDevice, &m_featureLevel, &deviceContext);
		if (SUCCEEDED(hr))
		{
			m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**) &m_pDXGIDevice);
			m_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &m_pDXGIAdapter);
			m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &m_pDXGIFactory);
			m_pDeviceContext = new DeviceContext(deviceContext);
			return true;
		}
	}
	return false;
}

void GraphicsEngine::Shutdown()
{
	GraphicsEngine::~GraphicsEngine();
}

GraphicsEngine::~GraphicsEngine()
{
	if (m_pDXGIFactory)
	{
		m_pDXGIFactory->Release();
		m_pDXGIFactory = nullptr;
	}
	if (m_pDXGIAdapter)
	{
		m_pDXGIAdapter->Release();
		m_pDXGIAdapter = nullptr;
	}
	if (m_pDXGIDevice)
	{
		m_pDXGIDevice->Release();
		m_pDXGIDevice = nullptr;
	}
	if (m_pDeviceContext)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = nullptr;
	}
	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return m_pDeviceContext;
}

ID3D11Device* GraphicsEngine::GetDevice()
{
	return m_pDevice;
}

//ID3D11DeviceContext* GraphicsEngine::GetDeviceContext()
//{
//	return m_pDeviceContext;
//}

IDXGIFactory* GraphicsEngine::GetDXGIFactory()
{
	return m_pDXGIFactory;
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
