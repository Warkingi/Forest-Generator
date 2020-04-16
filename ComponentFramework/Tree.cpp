#include "Tree.h"

using namespace GAME;

//Created by Noah.C

Tree::Tree(Vec3 pos_, TreeModel *model_) {

	pos = pos_;
	model = std::unique_ptr<TreeModel>(model_);

}

Tree::~Tree() {
	OnDestroy();
}

void Tree::OnDestroy() {
	
	/*if (model) delete model;
	model = nullptr;*/

}


void Tree::Update(const float deltaTime) {

	modelMatrix = MMath::translate(pos.x, pos.y, pos.z);

}

void Tree::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix)const {

	glUseProgram(model->shader->getProgram());
	glUniformMatrix4fv(model->projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(model->modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);
	glUniformMatrix3fv(model->normalMatrixID, 1, GL_FALSE, normalMatrix);
	for (int i = 0; i < model->meshes.size(); i++) {
		model->meshes[i]->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO

}