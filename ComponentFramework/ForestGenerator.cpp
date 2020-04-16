#include "ForestGenerator.h"

#include <iostream>

//Created by Noah.C

ForestGenerator::ForestGenerator(const int width_, const int length_) {

	treeModels.push_back(new TreeModel(1.0f));
	treeModels.push_back(new TreeModel(0.7f));
	treeModels.push_back(new TreeModel(1.3f));
	treeModels.push_back(new TreeModel(3.0f));
	GenerateTrees(width_, length_);

}

ForestGenerator::~ForestGenerator() {
	OnDestroy();
}

void ForestGenerator::OnDestroy() {
	for (int i = 0; i < treeModels.size(); i++) {
		if (treeModels[i]) delete treeModels[i];
		treeModels[i] = nullptr;
	}

	for (int i = 0; i < trees.size(); i++) {
		if (trees[i]) delete trees[i];
		trees[i] = nullptr;
	}
}

void ForestGenerator::GenerateTrees(const int width_, const int length_) {

	//Temp ints that store the size of the map.
	///Instead of just getting the width and length we need to draw the terrain so it aligns with the center.
	///This is easy, all we need to do is divide by two and negate the minimum. This will draw the terrain
	///equally in space.
	int minWidth = width_ / -2;
	int maxWidth = width_ / 2;

	int minLength = length_ / -2;
	int maxLength = length_ / 2;

	//Move the Rand() methods out of the push_back and set them to temp ints.
	//Use those two temp ints to call a new method that will find that point on the terrain
	//and get the height of that point. Set the height of that new tree to the height of the
	//point. BOOM! Insta tree on hill.


	for (int i = 0; i < (width_ * length_) / 128; i++) {

		trees.push_back(new Tree(Vec3((rand() % (maxWidth - minWidth + 1) + minWidth), 0,
			(rand() % (maxLength - minLength + 1) + minLength)),
			treeModels[(rand() % ((treeModels.size() - 1) - 0 + 1) + 0)]));

	}

}