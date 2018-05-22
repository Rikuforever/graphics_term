#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

class Camera
{
public:
	Camera();

	glm::mat4 getViewMatrix() const;

	virtual void setPosition(const glm::vec3& position);
	virtual void setLookAt(const glm::vec3& target);
	virtual void move(const glm::vec3& offsetPos);

	const glm::vec3& getLook() const;
	const glm::vec3& getRight() const;
	const glm::vec3& getUp() const;
protected:
	virtual void updateCameraVectors();

	glm::vec3 mPosition;
	glm::vec3 mTargetPos;
	glm::vec3 mLook;
	glm::vec3 mUp;
	glm::vec3 mRight;
	const glm::vec3 WORLD_UP;
};

class OrbitCamera : public Camera
{
public:
	OrbitCamera();

	virtual void setRotation(float yaw, float pitch);	// in degrees, yaw = from z-axis, pitch = from y(normal)-axis
	virtual void rotate(float yaw, float pitch);		// in degrees, yaw = from z-axis, pitch = from y(normal)-axis

	// Camera Controls
	void setRadius(float radius);

private:

	void updateCameraVectors() override;

	// Camera parameters
	float mRadius;
	// Euler Angles (in radians)
	float mYaw;
	float mPitch;
};

#endif	// CAMERA_H