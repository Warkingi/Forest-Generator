#include "Camera.h"

//Debugging
#include <iostream>

//Created by Noah.C

Camera::Camera(Vec3 pos_, Vec3 target_, Vec3 up_, float cameraSpeed_) {

	cameraPos = pos_;
	cameraTarget = target_;
	up = up_;

	cameraSpeed = cameraSpeed_;

	cameraFront = Vec3(0.0f, 0.0f, -1.0f);

	cameraDirection = VMath::normalize(cameraPos - cameraTarget);
	
	cameraRight = VMath::normalize(VMath::cross(up, cameraDirection));
	cameraUp = VMath::cross(cameraDirection, cameraRight);

	view = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f),
						Vec3(0.0f, 0.0f, 0.0f),
						Vec3(0.0f, 1.0f, 0.0f));
}

Camera::~Camera() {


}

void Camera::handleCameraEvents(const SDL_Event& SDLEvent) {

	switch (SDLEvent.type) {

	case SDL_KEYDOWN:
		switch (SDLEvent.key.keysym.sym) {
		case SDLK_w:
			cameraPos += cameraSpeed * cameraFront;
			break;
		case SDLK_s:
			cameraPos -= cameraSpeed * cameraFront;
			break;
		case SDLK_a:
			cameraPos -= VMath::normalize(VMath::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		case SDLK_d:
			cameraPos += VMath::normalize(VMath::cross(cameraFront, cameraUp)) * cameraSpeed;
			break;
		}

		break;
	default:
		break;
	}

}

void Camera::Update(float deltaTime) {

	view = MMath::lookAt(cameraPos,
						cameraPos + cameraFront,
						cameraUp);
	
}

Matrix4 Camera::getViewMatrix() {

	return view;
}