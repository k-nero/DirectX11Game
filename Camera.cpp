#include "Camera.h"

const XMFLOAT3 Camera::Up()
{
	auto temp = GMathFV(mUp) - GMathFV(mPosition);
	auto temp2 = GMathVF(temp);
	return temp2;
}

const XMFLOAT3 Camera::LookAtTarget()
{
	auto temp = GMathFV(mTarget) - GMathFV(mPosition);
	return GMathVF(temp);
}

const XMFLOAT4X4 Camera::View()
{
	auto temp = XMMatrixTranspose(GMathFM(mView));
	return GMathMF(temp);
}

const XMFLOAT4X4 Camera::Proj()
{
	auto temp = XMMatrixTranspose(GMathFM(mProj));
	return GMathMF(temp);
}

const XMFLOAT4X4 Camera::Ortho()
{
	auto temp = XMMatrixTranspose(GMathFM(mOrtho));
	return GMathMF(temp);
}


Camera::Camera(void)
{
	mPosition = XMFLOAT3(0.0f, 0.0f, 20.0f);
	mTarget = XMFLOAT3(0.0f, 0.0f, 0.0f);
	auto temp1 = XMFLOAT3(0, 1, 0);
	auto temp2 = GMathFV(mPosition);
	auto temp3 = temp2 + GMathFV(temp1);
	mUp = GMathVF(temp3);
	this->initViewMatrix();

	mAngle = 0.0f;
	mClientWidth = 0.0f;
	mClientHeight = 0.0f;
	mNearest = 0.0f;
	mFarthest = 0.0f;

	XMStoreFloat4x4(&mView, XMMatrixIdentity());
	XMStoreFloat4x4(&mProj, XMMatrixIdentity());
	XMStoreFloat4x4(&mOrtho, XMMatrixIdentity());
}

Camera::Camera(const Camera& camera)
{
	*this = camera;
}

Camera& Camera::operator=(const Camera& camera)
{
	mPosition = camera.mPosition;
	mTarget = camera.mTarget;
	mUp = camera.mUp;

	mAngle = camera.mAngle;
	mClientWidth = camera.mClientWidth;
	mClientHeight = camera.mClientHeight;
	mNearest = camera.mNearest;
	mFarthest = camera.mFarthest;

	mView = camera.mView;
	mProj = camera.mProj;
	mOrtho = camera.mOrtho;
	return *this;
}

void Camera::initViewMatrix()
{
	auto temp = this->Up();
	XMStoreFloat4x4(&mView, XMMatrixLookAtLH(XMLoadFloat3(&mPosition), XMLoadFloat3(&mTarget), XMLoadFloat3(&temp)));
}

void Camera::InitProjMatrix(const float angle, const float client_width, const float client_height, const float near_plane, const float far_plane)
{
	mAngle = angle;
	mClientWidth = client_width;
	mClientHeight = client_height;
	mNearest = near_plane;
	mFarthest = far_plane;
	XMStoreFloat4x4(&mProj, XMMatrixPerspectiveFovLH(angle, client_width / client_height, near_plane, far_plane));
}

void Camera::Move(XMFLOAT3 direction)
{
	auto temp = XMVector3Transform(GMathFV(mPosition), XMMatrixTranslation(direction.x, direction.y, direction.z));
	mPosition = GMathVF(temp);
	auto temp2 = XMVector3Transform(GMathFV(mTarget), XMMatrixTranslation(direction.x, direction.y, direction.z));
	mTarget = GMathVF(temp2);
	auto temp3 = XMVector3Transform(GMathFV(mUp), XMMatrixTranslation(direction.x, direction.y, direction.z));
	mUp = GMathVF(temp3);

	this->initViewMatrix();
}

void Camera::Rotate(XMFLOAT3 axis, float degrees)
{
	if (XMVector3Equal(GMathFV(axis), XMVectorZero()) || degrees == 0.0f)
	{
		return;
	}

	// rotate vectors
	auto temp1 = GMathFV(mTarget) - GMathFV(mPosition);
	XMFLOAT3 look_at_target = GMathVF(temp1);
	auto temp2 = GMathFV(mUp) - GMathFV(mPosition);
	XMFLOAT3 look_at_up = GMathVF(temp2);
	auto temp3 = XMVector3Transform(GMathFV(look_at_target), XMMatrixRotationAxis(GMathFV(axis), XMConvertToRadians(degrees)));
	look_at_target = GMathVF(temp3);
	auto temp4 = XMVector3Transform(GMathFV(look_at_up), XMMatrixRotationAxis(GMathFV(axis), XMConvertToRadians(degrees)));
	look_at_up = GMathVF(temp4);

	// restore vectors's end points mTarget and mUp from new rotated vectors
	auto temp5 = GMathFV(mPosition) + GMathFV(look_at_target);
	mTarget = GMathVF(temp5);
	auto temp6 = GMathFV(mPosition) + GMathFV(look_at_up);
	mUp = GMathVF(temp6);

	this->initViewMatrix();
}

void Camera::Target(XMFLOAT3 new_target)
{
	if (XMVector3Equal(GMathFV(new_target), GMathFV(mPosition)) || XMVector3Equal(GMathFV(new_target), GMathFV(mTarget)))
	{
		return;
	}

	auto temp1 = GMathFV(mTarget) - GMathFV(mPosition);
	XMFLOAT3 old_look_at_target = GMathVF(temp1);
	auto temp2 = GMathFV(new_target) - GMathFV(mPosition);
	XMFLOAT3 new_look_at_target = GMathVF(temp2);
	float angle = XMConvertToDegrees(XMVectorGetX( XMVector3AngleBetweenNormals(XMVector3Normalize(GMathFV(old_look_at_target)), XMVector3Normalize(GMathFV(new_look_at_target)))));
	if (angle != 0.0f && angle != 360.0f && angle != 180.0f)
	{
		XMVECTOR axis = XMVector3Cross(GMathFV(old_look_at_target), GMathFV(new_look_at_target));
		Rotate(GMathVF(axis), angle);
	}
	mTarget = new_target;
	this->initViewMatrix();
}

// Set camera position
void Camera::Position(XMFLOAT3& new_position)
{
	auto temp = GMathFV(new_position) - GMathFV(mPosition);
	XMFLOAT3 move_vector = GMathVF(temp);
	XMFLOAT3 target = mTarget;
	this->Move(move_vector);
	this->Target(target);
}

void Camera::NearestPlane(float nearest)
{
	mNearest = nearest;
	OnResize(mClientWidth, mClientHeight);
}

void Camera::FarthestPlane(float farthest)
{
	mFarthest = farthest;
	OnResize(mClientWidth, mClientHeight);
}

void Camera::InitOrthoMatrix(const float clientWidth, const float clientHeight,const float nearZ, const float fartherZ)
{
	XMStoreFloat4x4(&mOrtho, XMMatrixOrthographicLH(clientWidth, clientHeight, 0.0f, fartherZ));
}

void Camera::OnResize(float new_width, float new_height)
{
	mClientWidth = new_width;
	mClientHeight = new_height;
	InitProjMatrix(mAngle, static_cast<float>(new_width), static_cast<float>(new_height), mNearest, mFarthest);
	InitOrthoMatrix(static_cast<float>(new_width), static_cast<float>(new_height), 0.0f, mFarthest);
}
