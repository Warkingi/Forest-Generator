#include "SoundManager.h"

//Created by Noah.C

SoundManager::SoundManager() {

	SoundEngine = createIrrKlangDevice();

}

SoundManager::~SoundManager() {

	OnDestroy();

}

void SoundManager::OnDestroy() {
	if (SoundEngine) delete SoundEngine;
	SoundEngine = nullptr;
}

void SoundManager::setBackgroundMusic() {

	SoundEngine->play2D("ForestTheme.mp3", GL_TRUE);

}

void SoundManager::setAmbientSounds() {

	SoundEngine->play2D("ForestAmbience.mp3", GL_TRUE);

}