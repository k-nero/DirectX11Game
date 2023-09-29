#pragma once
#include <directxmath/DirectXMath.h>

__declspec(align(16)) struct constant
{
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;
};

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texcoord;
};