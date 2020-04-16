#ifndef CAMERA_H
#define CAMERA_H

#include "MMath.h"
#include "VMath.h"
#include "SDL.h"

//Created by Noah.C

using namespace MATH;

class Camera {

private:

	Vec3 cameraPos;
	Vec3 cameraTarget;

	Vec3 cameraDirection;

	Vec3 up;
	Vec3 cameraRight;

	Vec3 cameraUp;

	Vec3 cameraFront;

	Matrix4 view;

public:

	float cameraSpeed;

	//Constructor for initializing the camera.
	Camera(Vec3 pos_, Vec3 target_, Vec3 up_, float cameraSpeed_);
	~Camera();

	void handleCameraEvents(const SDL_Event& SDLEvent);

	void Update(float deltaTime);


	Matrix4 getViewMatrix();

};

#endif // !CAMERA_H
