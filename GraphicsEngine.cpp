#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine()
= default;

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

	for (auto m_driverType : driverTypes)
	{
		const HRESULT hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, creationFlags, featureLevels,ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_pDevice, &m_featureLevel, &deviceContext);
		if (SUCCEEDED(hr))
		{
			m_pDeviceContext = new DeviceContext(deviceContext);

			m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**) &m_pDXGIDevice);
			m_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &m_pDXGIAdapter);
			m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &m_pDXGIFactory);
#if defined(DEBUG)
			m_pDevice->QueryInterface(__uuidof(ID3D11Debug), (void**) &m_debug);
			m_debug->SetFeatureMask(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL);
			m_debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
			m_debug->ValidateContext(deviceContext);
			//m_debug->ValidateContextForDispatch(deviceContext);

			// create info queue object
			
			if (SUCCEEDED(m_debug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**) &pInfoQueue)))
			{
				pInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
				pInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
			}

			// configure info queue to break on warnings or error

			UINT64 numStoredMessages = pInfoQueue->GetNumStoredMessages();
			for (UINT64 i = 0; i < numStoredMessages; i++)
			{
				SIZE_T messageSize = 0;
				pInfoQueue->GetMessage(i, NULL, &messageSize);
				D3D11_MESSAGE* pMessage = (D3D11_MESSAGE*) malloc(messageSize);
				pInfoQueue->GetMessage(i, pMessage, &messageSize);
				std::cout << pMessage->ID << " - " << pMessage->pDescription << " - " << pMessage->Severity << " \r" << std::flush;
				free(pMessage);
			}
			pInfoQueue->ClearStoredMessages();
#endif
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
	if(pInfoQueue)
	{
		pInfoQueue->Release();
		pInfoQueue = nullptr;
	}
	if(m_debug)
	{
		m_debug->Release();
		m_debug = nullptr;
	}
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

DeviceContext* GraphicsEngine::GetImmediateDeviceContext() const
{
	return m_pDeviceContext;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	auto* vs = new VertexShader();
	if (!vs->Initialize(shader_byte_code, byte_code_size))
	{
		vs->Release();
		return nullptr;
	}
	return vs;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	auto* ps = new PixelShader();
	if (!ps->Initialize(shader_byte_code, byte_code_size))
	{
		ps->Release();
		return nullptr;
	}
	return ps;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", NULL, NULL, &m_blob, &error_blob);
	if (FAILED(hr) || error_blob)
	{
		if (error_blob)
		{
			std::string errorMessage = (char*) error_blob->GetBufferPointer();
			OutputDebugStringA(errorMessage.c_str());
			error_blob->Release();
			return false;
		}
		return false;
	}
	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();
	return false;
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", NULL, NULL, &m_blob, &error_blob);
	if (FAILED(hr) || error_blob)
	{
		if (error_blob)
		{
			std::string errorMessage = (char*) error_blob->GetBufferPointer();
			OutputDebugStringA(errorMessage.c_str());
			error_blob->Release();
		}
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (m_blob)
	{
		m_blob->Release();
		m_blob = nullptr;
	}
}

ID3D11Device* GraphicsEngine::GetDevice() const
{
	return m_pDevice;
}

IDXGIFactory* GraphicsEngine::GetDXGIFactory()
{
	return m_pDXGIFactory;
}

ID3D11DeviceContext* GraphicsEngine::GetDeviceContext()
{
	return this->deviceContext;
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
