#pragma once

#include <DirectXMath.h>

class Camera
{
public:
	Camera();
	Camera(const Camera& camera);
	~Camera();
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();

	void Render();
	DirectX::XMMATRIX GetViewMatrix();

private:
	float m_positionX;
	float m_positionY;
	float m_positionZ;
	float m_rotationX; 
	float m_rotationY;
	float m_rotationZ;
	DirectX::XMMATRIX m_viewMatrix{};
};