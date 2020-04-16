#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <irrKlang.h>
#include <GL/glew.h>

using namespace irrklang;

//Created by Noah.C

class SoundManager {

private:

	ISoundEngine *SoundEngine;

public:

	SoundManager();
	~SoundManager();

	void setBackgroundMusic();
	void setAmbientSounds();

	void OnDestroy();
};

#endif // !SOUNDMANAGER_H

