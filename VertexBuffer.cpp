#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Renderer* renderer) : m_renderer(renderer)
{

}

bool VertexBuffer::Load( void* list_vertices, unsigned int vertex_size, unsigned int list_size, const void* shader_byte_code, size_t shader_byte_size)
{
	if (m_layout)m_layout->Release();

	D3D11_BUFFER_DESC buffDesc = { vertex_size * list_size, D3D11_USAGE_DYNAMIC, D3D11_BIND_VERTEX_BUFFER, D3D11_CPU_ACCESS_WRITE, 0 };

	D3D11_MAPPED_SUBRESOURCE buffer_data = {};

	this->m_vertex_size = vertex_size;
	this->m_vertext_list_size = list_size;

	if (!m_buffer)
	{
		if ((m_renderer->GetDevice()->CreateBuffer(&buffDesc, nullptr, &m_buffer) < 0x0L))
		{
			return false;
		}
	}
	
	m_renderer->GetImmediateDeviceContext()->GetDeviceContext()->Map(m_buffer.Get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &buffer_data);
	memcpy(buffer_data.pData, list_vertices, static_cast<size_t>(vertex_size) * list_size);
	m_renderer->GetImmediateDeviceContext()->GetDeviceContext()->Unmap(m_buffer.Get(), NULL);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	unsigned size_layout = (sizeof(*RtlpNumberOf(layout)));

	auto hr = m_renderer->GetDevice()->CreateInputLayout(layout, size_layout, shader_byte_code, shader_byte_size, &m_layout);
	return hr >= 0x0L ? true : false;
}

void VertexBuffer::Release()
{
	VertexBuffer::~VertexBuffer();
	delete this;
}

VertexBuffer::~VertexBuffer() = default;

unsigned VertexBuffer::GetVertexListSize() const
{
	return (m_vertext_list_size);
}

unsigned int VertexBuffer::GetVertexSize() const
{
	return m_vertex_size;
}

ID3D11Buffer* VertexBuffer::GetBuffer() const
{
	return m_buffer.Get();
}

ID3D11InputLayout* VertexBuffer::GetLayout() const
{
	return m_layout.Get();
}
