#include "Primitive.h"

using namespace GAME;

Primitive::Primitive(GLenum drawMode_, std::vector<Vec3> &vertices_, std::vector<Vec3> &normals, std::vector<Vec2> &uvs_) {
	meshes.push_back(new Mesh(drawMode_, vertices_, normals, uvs_));
	vertices = vertices_;
	OnCreate();
}

Primitive::Primitive(std::string filePath_) {
	ObjLoader obj(filePath_.c_str());
	meshes.push_back(new Mesh(GL_LINE_LOOP, obj.vertices, obj.normals, obj.uvCoords));
	vertices = obj.vertices;
	OnCreate();
}

Primitive::~Primitive() {
	OnDestroy();
}

bool Primitive::OnCreate() {
	shader = new Shader("baseVert.glsl", "baseFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");
	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	return true;
}

void Primitive::OnDestroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	if (shader) {
		delete shader;
	}
	shader = nullptr;
	for (Mesh* m : meshes) {
		if (m) {
			delete m;
		}
		m = nullptr;
	}
}

void Primitive::Update(const float deltaTime) {
	
	modelMatrix = MMath::translate(pos.x, pos.y, pos.z);

}

void Primitive::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix)const {

	glUseProgram(shader->getProgram());
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO
}