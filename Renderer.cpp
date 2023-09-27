#include "Renderer.h"


Renderer::Renderer()
= default;

bool Renderer::Initialize()
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
	D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	for (const auto m_driverType : driverTypes)
	{
		const auto hr = D3D11CreateDevice(nullptr, m_driverType, nullptr, creationFlags, featureLevels, (sizeof(*RtlpNumberOf(featureLevels))), (0x7U), &m_pDevice, &m_featureLevel, &deviceContext);
		if (hr >= 0x0L)
		{
			m_pDeviceContext = std::make_shared<DeviceContext>(deviceContext.Get());
			m_pDevice->QueryInterface(__uuidof(IDXGIDevice), IID_PPV_ARGS_Helper(&m_pDXGIDevice));
			m_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), IID_PPV_ARGS_Helper(&m_pDXGIAdapter));
			m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), IID_PPV_ARGS_Helper(&m_pDXGIFactory));
#if defined(_DEBUG)
			m_pDevice->QueryInterface(__uuidof(ID3D11Debug), IID_PPV_ARGS_Helper(&m_debug));
			m_debug->SetFeatureMask(0x3U);
			m_debug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_DETAIL);
			m_debug->ValidateContext(deviceContext.Get());

			if ((m_debug->QueryInterface(__uuidof(ID3D11InfoQueue), IID_PPV_ARGS_Helper(&pInfoQueue))) >= 0x0L)
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

void Renderer::Shutdown()
{
	//Renderer::~Renderer();
}

Renderer::~Renderer()
{
}

std::shared_ptr<SwapChain> Renderer::CreateSwapChain()
{
	return std::make_shared<SwapChain>(this);
}

std::shared_ptr<IndexBuffer> Renderer::CreateIndexBuffer()
{
	return std::make_shared<IndexBuffer>(this);
}

DeviceContext* Renderer::GetImmediateDeviceContext() const
{
	return m_pDeviceContext.get();
}

std::shared_ptr<VertexBuffer> Renderer::CreateVertexBuffer()
{
	return std::make_shared<VertexBuffer>(this);
}

std::shared_ptr<ConstantBuffer> Renderer::CreateConstantBuffer()
{
	return std::make_shared<ConstantBuffer>(this);
}

std::shared_ptr<VertexShader> Renderer::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	auto vs = std::make_shared<VertexShader>(this);
	if (!vs->Initialize(shader_byte_code, byte_code_size))
	{
		return nullptr;
	}
	return vs;
}

std::shared_ptr<PixelShader> Renderer::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	auto ps = std::make_shared<PixelShader>(this);
	if (!ps->Initialize(shader_byte_code, byte_code_size))
	{
		return nullptr;
	}
	return ps;
}

bool Renderer::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob = nullptr;
	unsigned int flag = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined (_DEBUG)
	flag |= D3DCOMPILE_DEBUG;
#endif

	HRESULT hr = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", flag, NULL, &m_blob, &error_blob);
	if (FAILED(hr) || error_blob)
	{
		if (error_blob)
		{
			const std::string errorMessage = (char*)error_blob->GetBufferPointer();
			OutputDebugStringA(errorMessage.c_str());
			return false;
		}
		return false;
	}
	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();
	return false;
}

bool Renderer::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	Microsoft::WRL::ComPtr<ID3DBlob> error_blob = nullptr;
	unsigned int flag = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined (_DEBUG)
	flag |= D3DCOMPILE_DEBUG;
#endif
	HRESULT hr = D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", flag, NULL, &m_blob, &error_blob);
	if (FAILED(hr) || error_blob)
	{
		if (error_blob)
		{
			const std::string errorMessage = (char*)error_blob->GetBufferPointer();
			OutputDebugStringA(errorMessage.c_str());
			return false;
		}
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void Renderer::ReleaseCompiledShader()
{
	if (m_blob)
	{
		m_blob->Release();
		m_blob = nullptr;
	}
}

ID3D11InfoQueue* Renderer::GetInfoQueue() const
{
	return pInfoQueue.Get();
}

ID3D11Device* Renderer::GetDevice() const
{
	return m_pDevice.Get();
}

IDXGIFactory* Renderer::GetDXGIFactory()
{
	return m_pDXGIFactory.Get();
}
