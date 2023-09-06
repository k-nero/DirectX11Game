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
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	for (const auto m_driverType : driverTypes)
	{
		const auto hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, creationFlags, featureLevels, (sizeof(*RtlpNumberOf(featureLevels))), (0x7U), &m_pDevice, &m_featureLevel, &deviceContext);
		if (hr >= 0x0L)
		{
			m_pDeviceContext = new DeviceContext(deviceContext.Get());
			 
			m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**) &m_pDXGIDevice);
			m_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), IID_PPV_ARGS_Helper(&m_pDXGIAdapter));
			m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), IID_PPV_ARGS_Helper(&m_pDXGIFactory));
#if defined(_DEBUG)
			m_pDevice->QueryInterface(__uuidof(ID3D11Debug), (void**) &m_debug);
			m_debug->SetFeatureMask(0x3U);
			m_debug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_DETAIL);
			m_debug->ValidateContext(deviceContext.Get());
			//m_debug->ValidateContextForDispatch(deviceContext);

			if ((m_debug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**) &pInfoQueue)) >= 0x0L)
			{
				pInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
				pInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
			}
#endif
			return true;
		}
	}
	return false;
}

void GraphicsEngine::Shutdown()
{
	GraphicsEngine::~GraphicsEngine();
	//delete this;
}

GraphicsEngine::~GraphicsEngine()
{
	if (m_pDeviceContext)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = nullptr;
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

ConstantBuffer* GraphicsEngine::CreateConstantBuffer()
{
	return new ConstantBuffer();
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
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", NULL, NULL, &m_blob, &error_blob);
	if (FAILED(hr) || error_blob)
	{
		if (error_blob)
		{
			std::string errorMessage = (char*) error_blob->GetBufferPointer();
			OutputDebugStringA(errorMessage.c_str());
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
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob = nullptr;
	HRESULT hr = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", NULL, NULL, &m_blob, &error_blob);
	if (FAILED(hr) || error_blob)
	{
		if (error_blob)
		{
			std::string errorMessage = (char*) error_blob->GetBufferPointer();
			OutputDebugStringA(errorMessage.c_str());
			return false;
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

ID3D11InfoQueue* GraphicsEngine::GetInfoQueue() const
{
	return pInfoQueue.Get();
}

ID3D11Device* GraphicsEngine::GetDevice() const
{
	return m_pDevice.Get();
}

IDXGIFactory* GraphicsEngine::GetDXGIFactory()
{
	return m_pDXGIFactory.Get();
}

GraphicsEngine* GraphicsEngine::Get()
{
	static GraphicsEngine engine;
	return &engine;
}
