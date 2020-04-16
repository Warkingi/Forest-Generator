#include "TreeModel.h"

using namespace GAME;

//Created by Noah.C

TreeModel::TreeModel(float size_) {

	size = size_;

	OnCreate();

}

TreeModel::~TreeModel() {
	OnDestroy();
}

bool TreeModel::OnCreate() {

	ObjLoader obj("tree.obj");
	//Size modifier
	for (int i = 0; i < obj.vertices.size(); i++) {

		obj.vertices[i].x = obj.vertices[i].x * size;
		obj.vertices[i].y = obj.vertices[i].y * size;
		obj.vertices[i].z = obj.vertices[i].z * size;

	}
	meshes.push_back(std::unique_ptr<Mesh>(new Mesh(GL_TRIANGLES , obj.vertices, obj.normals, obj.uvCoords)));
	//modelTest();

	shader = std::unique_ptr<Shader>(new Shader("phongVert.glsl", "phongFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords"));
	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");

	return true;
}

void TreeModel::OnDestroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void TreeModel::modelTest() {
	ObjLoader obj("cube.obj");

	meshes.push_back(std::unique_ptr<Mesh>(new Mesh(GL_TRIANGLES, obj.vertices, obj.normals, obj.uvCoords)));
}