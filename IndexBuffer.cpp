#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Renderer* renderer): m_renderer(renderer)
{
}

bool IndexBuffer::Load(void* list_indices, UINT size_list)
{
	D3D11_BUFFER_DESC desc = {};
	memset(((&desc)), 0, ((sizeof(desc))));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = size_list * 4;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = list_indices;
	this->m_size_list = size_list;

	auto hr = m_renderer->GetDevice()->CreateBuffer(&desc, &data, &m_buffer);

	return hr >= 0x0L ? true : false;
}

void IndexBuffer::Release()
{
	IndexBuffer::~IndexBuffer();
	delete this;
}

IndexBuffer::~IndexBuffer() = default;

ID3D11Buffer* IndexBuffer::GetBuffer()
{
	return this->m_buffer.Get();
}

unsigned int IndexBuffer::GetIndexListSize() const
{
	return this->m_size_list;
}
