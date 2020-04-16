#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

#include "Terrain.h"
#include "ForestGenerator.h"

#include <GL/glew.h>
#include <memory>

//Created by Noah.C

class TerrainGenerator {

private:
	
	std::shared_ptr<Terrain> terrain;
	//Terrain* terrain;
	std::shared_ptr<ForestGenerator> forest;
	//ForestGenerator *forest;

public:

	//Generate new terrain with given params Width && Height and random height map
	TerrainGenerator(const int width_, const int length_);
	//TerrainGenerator(filename); Perhaps I will implement file reading to generate map someday
	~TerrainGenerator();

	void OnDestroy();

	//Returns the generated terrain as a pointer
	inline std::shared_ptr<Terrain> getTerrain() const { return terrain; }
	inline std::shared_ptr<ForestGenerator> getForest() const { return forest; }
	/*inline Terrain* getTerrain() const { return terrain; }
	inline ForestGenerator* getForest() const { return forest; }*/

};
#endif // !TERRAINGENERATOR_H