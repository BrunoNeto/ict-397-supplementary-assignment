#include "camera.h"

#include <iostream>
using namespace std;

CCamera::CCamera()
{
	position = vec3(0.0, 0.0, 0.0);
	lookAt = vec3(0.0, 0.0, 1.0);

	forward = lookAt;
	up = vec3(0.0, 1.0, 0.0);
	right = vec3(1.0, 0.0, 0.0);

	velocity = vec3(0.0, 0.0, 0.0);
	acceleration = vec3(0.0, 0.0, 0.0);

	yaw = 0.0;
	pitch = 0.0;
}
/*
CCamera::CCamera(vector3D *look)
{
	position = vector3D(0.0, 0.0, 0.0);
	lookAt = look->UnitVector();

	forward = lookAt;
	up = vector3D(0.0, 1.0, 0.0);
	right = forward.CrossProduct(up); //vector3D(1.0, 0.0, 0.0);

	velocity = vector3D(0.0, 0.0, 0.0);
	acceleration = vector3D(0.0, 0.0, 0.0);

	yaw = 0.0;
	pitch = 0.0;
}
*/
/*
CCamera::CCamera(vector3D *pos, vector3D *look)
{
	position = *pos;
	lookAt = look->UnitVector();

	forward = lookAt;
	up = vector3D(0.0, 1.0, 0.0);
	right = vector3D(1.0, 0.0, 0.0);

	velocity = vector3D(0.0, 0.0, 0.0);
	acceleration = vector3D(0.0, 0.0, 0.0);

	yaw = 0.0;
	pitch = 0.0;
}
*/
CCamera::~CCamera()
{
}

void CCamera::UpdateLookAt()
{
	vec3 look = vec3(finalLookAt.x - lookAt.x,
		finalLookAt.y - lookAt.y,
		finalLookAt.z - lookAt.z);

	lookAtVel.x = (look.x) * 0.5;
	lookAtVel.y = (look.y) * 0.5;
	lookAtVel.z = (look.z) * 0.5;
}

void CCamera::UpdateMoveTo()
{
	vec3 pos = vec3(finalPosition.x - position.x,
		finalPosition.y - position.y,
		finalPosition.z - position.z);

	velocity.x = pos.x * 0.5;
	velocity.y = pos.y * 0.5;
	velocity.z = pos.z * 0.5;
}

void CCamera::RotatePitch(float radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);

	up.y = cosine * up.length();
	up.z = sine * up.length();

	forward.y = -sine * forward.length();
	forward.z = cosine * forward.length();
	/*     x   y      z       p
		 |  1  0       0       0 |
	 M = |  0  cos(A) -sin(A)  0 |
		 |  0  sin(A)  cos(A)  0 |
		 |  0  0       0       1 |
	*/
}

void CCamera::RotateYaw(float radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);

	right.x = cosine * right.length();
	right.z = sine * right.length();

	forward.x = -sine * forward.length();
	forward.z = cosine * forward.length();

	/*	   x      y    z      p
		 |  cos(A)  0  -sin(A)  0 |
	 M = |  0       1   0       0 |
		 |  sin(A)  0   cos(A)  0 |
		 |  0       0   0       1 |
	*/

}

void CCamera::RotateRoll(float radians)
{
	float sine = sinf(radians);
	float cosine = cosf(radians);

	right.x = cosine * right.length();
	right.y = sine * right.length();

	up.x = -sine * forward.length();
	up.y = cosine * forward.length();
	/*
		 |  cos(A)  -sin(A)   0   0 |
	 M = |  sin(A)   cos(A)   0   0 |
		 |  0        0        1   0 |
		 |  0        0        0   1 |
	*/
}


void CCamera::LookAtNow(vec3& pos)
{
	lookAt = pos;
}

void CCamera::MoveToNow(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}


void CCamera::MoveToNow(const vec3& pos)
{
	position = pos;
}

// look at an object over time
void CCamera::LookAt(const vec3& pos)
{
	vec3 v = vec3(pos - lookAt);

	initLookAt = lookAt;
	finalLookAt = pos;

	lookAtAccel = -lookAt * 0.25f;

	UpdateLookAt();
}

// move to an object over time
void CCamera::MoveTo(const vec3& pos)
{
	vec3 v = vec3(pos - position);

	initPosition = position;
	finalPosition = pos;

	acceleration = -position * 0.25f;

	UpdateMoveTo();
}
float degToRad(float value) 
{
	float rad = value * 0.0175;
	return rad;
}
void CCamera::Animate(float deltaTime)
{
	if ((yaw >= 360.0f) || (yaw <= -360.0f))
		yaw = 0.0f;

	if (pitch > 60.0f)
		pitch = 60.0f;
	if (pitch < -60.0f)
		pitch = -60.0f;

	// calculate trig functions
	float cosYaw = (float)cos(degToRad(yaw));
	float sinYaw = (float)sin(degToRad(yaw));
	float sinPitch = (float)sin(degToRad(pitch));

	// speed is velocity z-component
	float speed = velocity.z * deltaTime;

	// strafe speed is velocity x-component
	float strafeSpeed = velocity.x * deltaTime;

	// speed limit
	if (speed > 15.0)
		speed = 15.0;
	if (strafeSpeed > 15.0)
		strafeSpeed = 15.0;
	if (speed < -15.0)
		speed = -15.0;
	if (strafeSpeed < -15.0)
		strafeSpeed = -15.0;

	// friction
	if (velocity.length() > 0.0)
		acceleration = -velocity * 1.5f;

	velocity += acceleration * deltaTime;
	// calculate new position of camera
	position.x += float(cos(degToRad(yaw + 90.0)))*strafeSpeed;
	position.z += float(sin(degToRad(yaw + 90.0)))*strafeSpeed;
	position.x += float(cosYaw)*speed;
	position.z += float(sinYaw)*speed;
	//position.y = gameWorld.getWorldXZHeight(position.x, position.z) + 1.5;
	// calculate lookAt based on new position
	lookAt.x = float(position.x + cosYaw);
	lookAt.y = float(position.y + sinPitch);
	lookAt.z = float(position.z + sinYaw);

	// set the camera
	gluLookAt(position.x, position.y, position.z,
		lookAt.x, lookAt.y, lookAt.z,
		0.0, 1.0, 0.0);
}
