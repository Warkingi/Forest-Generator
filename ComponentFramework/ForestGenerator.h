#ifndef FORESTGENERATOR_H
#define FORESTGENERATOR_H

#include "Tree.h"

using namespace GAME;

//Created by Noah.C

class ForestGenerator {

	/*The ForestGenerator is for creating forests around the map.
	The generator takes in the size of the world and places trees 
	within that range. This makes for some cool randomly generated
	forests. ForestGenerator creates different tree models it can choose
	from and makes trees out of them using flyweigh design. This makes it
	less impactful on memory.*/

private:
	//Generate trees with the given width and length of the terrain.
	void GenerateTrees(const int width_, const int length_);

public:

	//Create a forest with the given width and length of the terrain.
	ForestGenerator(const int width_, const int length_);
	~ForestGenerator();

	void OnDestroy();

	std::vector<class TreeModel*> treeModels;
	std::vector<class Tree*> trees;

};

#endif // !FORESTGENERATOR_H
