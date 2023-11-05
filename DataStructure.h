#pragma once
#include <directxmath/DirectXMath.h>

__declspec(align(16)) struct constant
{
	DirectX::XMMATRIX m_world;
	DirectX::XMMATRIX m_view;
	DirectX::XMMATRIX m_projection;
	DirectX::XMFLOAT4 m_light_direction;
	DirectX::XMFLOAT4 camera_position;
};

struct Vertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT3 normal;
};