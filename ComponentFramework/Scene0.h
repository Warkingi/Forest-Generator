#ifndef Scene0_H
#define Scene0_H

#include "Scene.h"
#include "Window.h"
#include "Camera.h"
#include "Primitive.h"
#include "TerrainGenerator.h"
#include "SoundManager.h"

#include "Player.h"

//Created by Noah.C

namespace GAME {
	/// Forward casting
	class Trackball;

	class Scene0 : public Scene  {
	
	private:
			Vec3 lightPos;

			std::unique_ptr<SoundManager> sound;

			std::unique_ptr<Trackball> trackball;
			std::unique_ptr<Camera> camera;

			std::unique_ptr<TerrainGenerator> terrain;
			///FOR TESTING - SEE MORE IN CPP
			std::unique_ptr<Player> player;
			//TerrainGenerator *terrain;
		
	public:
		explicit Scene0(Window& windowRef);
		virtual ~Scene0();


		/// Delete these possible default constructors and operators  
		Scene0(const Scene0&) = delete;
		Scene0(Scene0 &&) = delete;
		Scene0& operator=(const Scene0 &) = delete;
		Scene0& operator=(Scene0 &&) = delete;

		virtual bool OnCreate() ;
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render() const;
		virtual void HandleEvents(const SDL_Event &SDLEvent);
		virtual void OnResize(const int, const int);
	
	
	};
}
#endif