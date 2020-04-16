#include <GL/glew.h>
#include <SDL.h>
#include "Scene0.h"
#include <iostream>
#include "MMath.h"
#include "QuadSphere.h"
#include "Model0.h"
#include "Trackball.h"
#include "Collider.h"

using namespace GAME;
using namespace MATH;

//Created by Noah.C

Scene0::Scene0(class Window& windowRef):  Scene(windowRef) { 
	trackball = std::unique_ptr<Trackball>(new Trackball());
	projectionMatrix.loadIdentity();
	viewMatrix.loadIdentity();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Scene0::~Scene0(){ 
	OnDestroy();
}

bool Scene0::OnCreate() {
	///PLAYER IS FOR TESTING
	player = std::unique_ptr<Player>(new Player());
	OnResize(windowPtr->GetWidth(),windowPtr->GetHeight());

	/// Load Assets: as needed 
	lightPos = Vec3(10.0f, 3.0f, 10.0f);
	//Create the terrain, let it handle the environment.
	terrain = std::unique_ptr<TerrainGenerator>(new TerrainGenerator(800, 800));
	
	///Testing methods here.
	player;

	sound = std::unique_ptr<SoundManager>(new SoundManager());

	sound->setBackgroundMusic();
	sound->setAmbientSounds();

	return true;
}


void Scene0::OnResize(int w_, int h_){
	windowPtr->SetWindowSize(w_,h_);
	glViewport(0,0,windowPtr->GetWidth(),windowPtr->GetHeight());
	float aspect = float(windowPtr->GetWidth()) / float(windowPtr->GetHeight());
	
	projectionMatrix = MMath::perspective(45.0f, aspect, 1.0f, 1000.0f);

	camera = std::unique_ptr<Camera>(new Camera(Vec3(0.0f, 1.5f, 10.0f), 
						Vec3(0.0f, 0.0f, 0.0f), 
						Vec3(0.0f, 1.0f, 0.0f),
						0.5f));//CameraSpeed

	viewMatrix = camera->getViewMatrix();
	
}

void Scene0::OnDestroy() {
	/// Cleanup Assets
}

void Scene0::Update(const float deltaTime){

	camera->Update(deltaTime);
	viewMatrix = camera->getViewMatrix();

	for (int i = 0; i < terrain->getForest()->trees.size(); i++) {
		if(terrain->getForest()->trees[i]) terrain->getForest()->trees[i]->Update(deltaTime);
	}
	
}

void Scene0::Render() const{
	/// Draw your scene here
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	for (int i = 0; i < terrain->getForest()->trees.size(); i++) {
		terrain->getForest()->trees[i]->Render(projectionMatrix, viewMatrix, trackball->GetMatrix3());
	}
	terrain->getTerrain()->Render(projectionMatrix, viewMatrix, trackball->GetMatrix3());
	SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}

void Scene0::HandleEvents(const SDL_Event& SDLEvent){
	camera->handleCameraEvents(SDLEvent);
}