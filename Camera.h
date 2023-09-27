#pragma once

#include <DirectXMath.h>
#include <Windows.h>

class Camera
{
public:
	Camera();
	Camera(const Camera& camera);
	Camera(DirectX::XMVECTOR init_camera_pos, DirectX::XMVECTOR init_world_up, float ini_yaw, float init_pitch, float movement_speed, float mouse_sensitive);
	~Camera();
	
	void KeyControl(int keys, float delta_time);
	void MouseControl(float x, float y);
	void UpdateViewMatrix();
	DirectX::XMMATRIX GetViewMatrix();

private:
	DirectX::XMVECTOR m_camera_pos{};
	DirectX::XMVECTOR m_camera_front{};
	DirectX::XMVECTOR m_camera_up{};
	DirectX::XMVECTOR m_camera_right{};
	DirectX::XMVECTOR m_world_up{0, 1, 0};

	float m_yaw;
	float m_pitch;

	float m_movement_speed;
	float m_mouse_sensitive;
};