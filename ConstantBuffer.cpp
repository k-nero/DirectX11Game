#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer() = default;

bool ConstantBuffer::Load(void* buffer, unsigned size)
{
	if (m_buffer != nullptr)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = size;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = buffer;

	auto hr = GraphicsEngine::Get()->GetDevice()->CreateBuffer(&desc, &data, &m_buffer);

	return hr >= 0x0L ? true : false;
}

void ConstantBuffer::Update(DeviceContext* deviceContext, void* buffer)
{
	deviceContext->GetDeviceContext()->UpdateSubresource(m_buffer.Get(), NULL, NULL, buffer, NULL, NULL);
}

void ConstantBuffer::Release()
{
	ConstantBuffer::~ConstantBuffer();
	delete this;
}

ConstantBuffer::~ConstantBuffer() = default;

ID3D11Buffer* ConstantBuffer::GetBuffer()
{
	return m_buffer.Get();
}
