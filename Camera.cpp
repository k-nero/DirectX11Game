#include "Camera.h"

Camera::Camera() = default;

Camera::Camera(const Camera& camera)
{
	this->m_camera_pos = camera.m_camera_pos;
	this->m_world_up = camera.m_world_up;
	this->m_yaw = camera.m_yaw;
	this->m_pitch = camera.m_pitch;
	this->m_movement_speed = camera.m_movement_speed;
	this->m_mouse_sensitive = camera.m_mouse_sensitive;
}

Camera::Camera(DirectX::XMVECTOR init_camera_pos, DirectX::XMVECTOR init_world_up, float init_yaw, float init_pitch, float movement_speed, float mouse_sensitive)
{
	this->m_camera_pos = init_camera_pos;
	this->m_world_up = init_world_up;
	this->m_yaw = init_yaw;
	this->m_pitch = init_pitch;
	this->m_movement_speed = movement_speed;
	this->m_mouse_sensitive = mouse_sensitive;
}

Camera::~Camera()
{
}

void Camera::KeyControl(int key, float delta_time)
{
	if (key == 'W')
	{
		m_camera_pos = DirectX::XMVectorAdd(m_camera_pos, DirectX::XMVectorScale(m_camera_front, delta_time * this->m_movement_speed));
	}
	if (key == 'S')
	{
		m_camera_pos = DirectX::XMVectorSubtract(m_camera_pos, DirectX::XMVectorScale(m_camera_front, delta_time * this->m_movement_speed));
	}
	if (key == 'A')
	{
		m_camera_pos = DirectX::XMVectorAdd(m_camera_pos, DirectX::XMVectorScale(m_camera_right, delta_time * this->m_movement_speed));
	}
	if (key == 'D')
	{
		m_camera_pos = DirectX::XMVectorSubtract(m_camera_pos, DirectX::XMVectorScale(m_camera_right, delta_time * this->m_movement_speed));
	}
	if (key == VK_SPACE)
	{
		m_camera_pos = DirectX::XMVectorAdd(m_camera_pos, DirectX::XMVectorScale(m_camera_up, delta_time * this->m_movement_speed));
	}
	if (key == VK_LSHIFT)
	{
		m_camera_pos = DirectX::XMVectorSubtract(m_camera_pos, DirectX::XMVectorScale(m_camera_up, delta_time * this->m_movement_speed));
	}
}

void Camera::MouseControl(int x, int y)
{
	x *= m_mouse_sensitive;
	y *= m_mouse_sensitive;

	m_yaw -= x;
	m_pitch -= y;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}

	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}
}

void Camera::UpdateViewMatrix()
{
	DirectX::XMVECTOR front{
		cos(DirectX::XMConvertToRadians(m_yaw))* cos(DirectX::XMConvertToRadians(m_pitch)),
		sin(DirectX::XMConvertToRadians(m_pitch)),
		sin(DirectX::XMConvertToRadians(m_yaw))* cos(DirectX::XMConvertToRadians(m_pitch))};
	front = DirectX::XMVector3Normalize(front);
	m_camera_front = front;

	m_camera_right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(m_camera_front, m_world_up));
	m_camera_up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(m_camera_right, m_camera_front));
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	return DirectX::XMMatrixLookAtLH(m_camera_pos, DirectX::XMVectorAdd(m_camera_pos, m_camera_front), m_camera_up);
}
// Path: GameWindow.cpp