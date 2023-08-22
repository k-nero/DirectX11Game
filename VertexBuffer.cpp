#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
}

bool VertexBuffer::Load(void* list_vertices, unsigned int size_vertex, unsigned int size_list, void* shader_byte_code, unsigned int size_byte_shader)
{
	if (m_buffer)m_buffer->Release();
	if (m_layout)m_layout->Release();

	GraphicsEngine* graphEngine = GraphicsEngine::Get();

	D3D11_BUFFER_DESC buffDesc = { size_vertex * size_list, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0 };

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	this->m_vertex_size = size_vertex;
	this->m_vertext_list_size = size_list;

	if(FAILED(graphEngine->GetDevice()->CreateBuffer(&buffDesc, &init_data, &m_buffer)))
	{
		return false;
	}
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	unsigned size_layout = ARRAYSIZE(layout);

	auto hr = graphEngine->GetDevice()->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout);
	return SUCCEEDED(hr) ? true : false;
}

void VertexBuffer::Release()
{
	VertexBuffer::~VertexBuffer();
	delete this;
}

VertexBuffer::~VertexBuffer()
{
	if (m_layout)
	{
		m_layout->Release();
		m_layout = nullptr;
	}
	if (m_buffer)
	{
		m_buffer->Release();
		m_buffer = nullptr;
	}
}

unsigned VertexBuffer::GetVertexListSize()
{
	return (m_vertext_list_size);
}

unsigned int VertexBuffer::GetVertexSize()
{
	return m_vertex_size;
}

ID3D11Buffer* VertexBuffer::GetBuffer()
{
	return m_buffer;
}

ID3D11InputLayout* VertexBuffer::GetLayout()
{
	return m_layout;
}
