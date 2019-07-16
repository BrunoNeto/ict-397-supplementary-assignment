#pragma once
#include "gtest/gtest.h"
#include "Camera.h"

TEST(Camera,CameraInitialisation) 
{
	//variables equal to the default constructor variables
	vec3 position = vec3(0.0, 0.0, 0.0);
	vec3 lookAt = vec3(0.0, 0.0, 1.0);

	vec3 forward = lookAt;
	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 right = vec3(1.0, 0.0, 0.0);

	vec3 velocity = vec3(0.0, 0.0, 0.0);
	vec3 acceleration = vec3(0.0, 0.0, 0.0);

	float yaw = 0.0;
	float pitch = 0.0;
	//tests instantiation by creating a cam object
	CCamera cam;
	//tests that all variables where initialised correctly
	ASSERT_EQ(position, cam.position);
	ASSERT_EQ(lookAt, cam.lookAt);
	ASSERT_EQ(forward, cam.forward);
	ASSERT_EQ(up, cam.up);
	ASSERT_EQ(right, cam.right);
	ASSERT_EQ(velocity, cam.velocity);
	ASSERT_EQ(acceleration, cam.acceleration);
	ASSERT_EQ(yaw, cam.yaw);
	ASSERT_EQ(pitch, cam.pitch);
	//if we reach succeed clause without error test is passed
	SUCCEED();
	
}
