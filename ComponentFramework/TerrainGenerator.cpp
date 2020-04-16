#include "TerrainGenerator.h"

#include <iostream> //Debugging

//Created by Noah.C

TerrainGenerator::TerrainGenerator(const int width_, const int length_) {

	terrain = std::shared_ptr<Terrain>(new Terrain(width_, length_));

	forest = std::shared_ptr<ForestGenerator>(new ForestGenerator(width_, length_));
}

TerrainGenerator::~TerrainGenerator() {
	OnDestroy();
}

void TerrainGenerator::OnDestroy() {

}

