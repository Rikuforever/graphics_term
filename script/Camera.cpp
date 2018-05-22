#include "Camera.h"
#include "glm/gtx/transform.hpp"

#define RADIUS_DEFAULT 10.0f
#define RADIUS_MAX 80.0f
#define RADIUS_MIN 2.0f

Camera::Camera()
	: mPosition(0.0f,0.0f,0.0f),
	mTargetPos(0.0f,0.0,0.0f),
	mUp(0.0f,1.0f,0.0f),
	mRight(0.0f,0.0f,0.0f),
	WORLD_UP(0.0f,1.0f,0.0f)
{
}

void Camera::updateCameraVectors()
{
	mLook = glm::normalize(mTargetPos - mPosition);
	mRight = glm::normalize(glm::cross(mLook, WORLD_UP));
	mUp = glm::normalize(glm::cross(mRight, mLook));
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(mPosition, mTargetPos, mUp);
}

void Camera::setPosition(const glm::vec3& position)
{
	mPosition = position;
	updateCameraVectors();
}

void Camera::setLookAt(const glm::vec3& target)
{
	mTargetPos = target;
	updateCameraVectors();
}

void Camera::move(const glm::vec3& offsetPos)
{
	mPosition += offsetPos;
	mTargetPos += offsetPos;
}


const glm::vec3& Camera::getLook() const
{
	return mLook;
}
const glm::vec3& Camera::getRight() const
{
	return mRight;
}
const glm::vec3& Camera::getUp() const
{
	return mUp;
}

// OrbitCamera

OrbitCamera::OrbitCamera()
	: mYaw(glm::pi<float>()),
	mPitch(0.0f)
{
}

void OrbitCamera::setRadius(float radius)
{
	mRadius = glm::clamp(radius, RADIUS_MIN, RADIUS_MAX);
}

void OrbitCamera::setRotation(float yaw, float pitch)
{
	mYaw = glm::radians(yaw);
	mPitch = glm::radians(pitch);

	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

	updateCameraVectors();
}


void OrbitCamera::rotate(float yaw, float pitch)
{
	mYaw += glm::radians(yaw);
	mPitch += glm::radians(pitch);

	mPitch = glm::clamp(mPitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

	updateCameraVectors();
}

void OrbitCamera::updateCameraVectors()
{
	mPosition.x = mTargetPos.x + mRadius * cosf(mPitch) * sinf(mYaw);
	mPosition.y = mTargetPos.y + mRadius * sinf(mPitch);
	mPosition.z = mTargetPos.z + mRadius * cosf(mPitch) * cosf(mYaw);
}
