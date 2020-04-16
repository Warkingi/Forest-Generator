#ifndef TREE_H
#define TREE_H

#include "TreeModel.h"
#include <memory>

//Created by Noah.C

namespace GAME {
	class Tree {

	private:

		std::unique_ptr<TreeModel> model;
		//TreeModel* model;
		Matrix4 modelMatrix;

		Vec3 pos;
		Vec3 vel;
		Vec3 orientation;
		Vec3 gravity;

		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;

	public:

		//Create a tree using the params of a position and the model it will use.
		Tree(Vec3 pos_, TreeModel *model_);
		~Tree();

		void OnDestroy();
		void Update(const float deltaTime);
		void Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix)const;

		inline Vec3 getPosition() const { return pos; } //Get the position of the tree

	};
}
#endif
