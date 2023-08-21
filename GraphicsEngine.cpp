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

	unsigned creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

	HRESULT hr;
	for (unsigned driverTypeIndex = 0; driverTypeIndex < ARRAYSIZE(driverTypes); driverTypeIndex++)
	{
		auto m_driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(NULL, m_driverType, NULL, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_pDevice, &m_featureLevel, &deviceContext);
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
	if (m_vs)
	{
		m_vs->Release();
		m_vs = nullptr;
	}

	if (m_ps)
	{
		m_ps->Release();
		m_ps = nullptr;
	}
	if (m_vsblob)
	{
		m_vsblob->Release();
		m_vsblob = nullptr;
	}
	if (m_psblob)
	{
		m_psblob->Release();
		m_psblob = nullptr;
	}

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

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

void GraphicsEngine::CreateShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_pDevice->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_pDevice->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
}

void GraphicsEngine::SetShaders()
{
	deviceContext->VSSetShader(m_vs, nullptr, 0);
	deviceContext->PSSetShader(m_ps, nullptr, 0);
}

void GraphicsEngine::GetShaderBufferAndSize(void** byteCode, unsigned *size)
{
	*byteCode = this->m_vsblob->GetBufferPointer();
	*size = static_cast<unsigned int>(this->m_vsblob->GetBufferSize());
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
