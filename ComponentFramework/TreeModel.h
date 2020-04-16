#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "MMath.h"
#include "Mesh.h"
#include "ObjLoader.h"
#include "Shader.h"

#include <memory>

//Created by Noah.C

namespace GAME {
	class TreeModel {

	private:

		float size;

	public:

		std::vector<std::unique_ptr<Mesh>> meshes;
		std::unique_ptr<Shader> shader;

		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;

		Sphere bounding;

		GLuint vbo;
		GLuint vao;

	public:

		TreeModel(float size_);
		~TreeModel();
		
		bool OnCreate();
		void OnDestroy();

		void modelTest();

		inline float TreeModel::getSize() { return size; } //Return the size modifier on the tree.

	};
}

#endif

