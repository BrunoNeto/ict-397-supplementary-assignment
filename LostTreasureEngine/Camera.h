#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Terrain.h"
using namespace std;
using namespace glm;
//	@brief CCamera class for our camera
//	@author Bruno Neto
//	version 1.0
class CObject;

class CCamera
{
private:
	 
	// these are used for moving and changing camera orientation
	// through the MoveTo/LookTo methods
	vec3 initPosition, finalPosition;
	vec3 initLookAt, finalLookAt;

	vec3 lookAtVel;			// velocity for looking at objects
	vec3 lookAtAccel;		// acceleration for looking at objects
	/**
	*	@brief method updating cameras lookat vector
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void UpdateLookAt();
	/**
	*	@brief method updating cameras moveto vector
	*   @see
	*	@param
	*	@return void
	*	@pre
	*	@post
	*/
	void UpdateMoveTo();

public:
	vec3 position;			// position of camera
	vec3 velocity;			// velocity of camera
	vec3 acceleration;		// acceleration of camera
	vec3 lookAt;			// lookat vector

	// up, forward, right vectors
	vec3 up;
	vec3 forward;
	vec3 right;

	// yaw and pitch angles
	float yaw;
	float pitch;

	int screenWidth, screenHeight;
	int centerX, centerY;
	/**
	*	@brief CCamera default contructor
	*   @see
	*	@param
	*	@return 
	*	@pre
	*	@post
	*/
	CCamera();
	/**
	*	@brief  CCamera contructor with given parameters
	*   @see
	*	@param width int to store width variable
	*	@param height int to store height variable
	*	@return 
	*	@pre
	*	@post
	*/
	CCamera(int width, int height) {}
	/**
	*	@brief CCamera deconstructor 
	*   @see
	*	@param
	*	@return 
	*	@pre
	*	@post
	*/
	~CCamera();
	/**
	*	@brief method for setting cameras lookat vector
	*   @see
	*	@param pos the position to use when updating look at
	*	@return void
	*	@pre
	*	@post
	*/
	void LookAt(const vec3& pos);
	/**
	*	@brief method changing the view to reflect the current look at vector
	*   @see
	*	@param	pos the position to use when looking
	*	@return void
	*	@pre
	*	@post
	*/
	void LookAtNow(vec3& pos);
	/**
	*	@brief method setting cameras moveto vector to a specific position
	*   @see
	*	@param pos the position to use when updating moveto vector
	*	@return void
	*	@pre
	*	@post
	*/
	void MoveTo(const vec3& pos);
	/**
	*	@brief method changing the view to reflect the current moveto vector
	*   @see
	*	@param	pos the position to use when moving
	*	@return void
	*	@pre
	*	@post
	*/
	void MoveToNow(const vec3& pos);
	/**
	*	@brief method changing the view to reflect the current moveto vector
	*   @see
	*	@param x the x value of the position
	*	@param y the y value of the position
	*	@param z the z value of the position
	*	@return void
	*	@pre
	*	@post
	*/
	void MoveToNow(float x, float y, float z);

	// right rotation along y-axis (yaw)
	/**
	*	@brief method for rotating yaw by the given amount
	*   @see
	*	@param radians the amount of rotation needed
	*	@return void
	*	@pre
	*	@post
	*/
	void RotateYaw(float radians);
	
	/**
	*	@brief method for rotating pitch by the given amount
	*   @see
	*	@param radians the amount of rotation needed
	*	@return void
	*	@pre
	*	@post
	*/
	void RotatePitch(float radians);
	/**
	*	@brief method for rotating roll by the given amount
	*   @see
	*	@param radians the amount of rotation needed
	*	@return void
	*	@pre
	*	@post
	*/
	void RotateRoll(float radians);

	// do physics calculations
	/**
	*	@brief method animating the cameras movement
	*   @see
	*	@param deltaTime the amount of time to animate for
	*	@return void
	*	@pre
	*	@post
	*/
	void Animate(float deltaTime,Terrain& t);//should prob pass this in by reference or work directly with heightmap
	
	
};
