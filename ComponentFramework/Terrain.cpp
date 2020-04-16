#include "Terrain.h"

//Debug
#include <iostream>

//Created by Noah.C

Terrain::Terrain(int width_, int length_) {

	width = width_;
	length = length_;

	OnCreate();
}

Terrain::~Terrain() {
	OnDestroy();
}

bool Terrain::OnCreate() {

	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<Vec2> uvs;

	for (int x = (length / -2); x < ((length / 2) + 1); x++) {
		for (int z = (width / -2); z < ((width / 2) + 1); z++) {
			vertices.push_back(Vec3(x, 0.0f, z));
			normals.push_back(Vec3(1.0f, 1.0f, 1.0f));
			uvs.push_back(Vec2(1.0f, 0.0f));
		}
		for (int z = (width / 2); z > ((width / -2) - 1); z--) {
			vertices.push_back(Vec3(x + 1.0f, 0.0f, z));
			normals.push_back(Vec3(1.0f, 1.0f, 1.0f));
			uvs.push_back(Vec2(1.0f, 0.0f));
		}
	}

	//heightMap->insert(std::make_pair(Vec2(0.0f, 0.0f), 0.0f));

	//std::cout << heightMap->at(Vec2(0.0f, 0.0f)) << std::endl;

	mesh = std::unique_ptr<Mesh>(new Mesh(GL_POINTS, vertices, normals, uvs));

	shader = std::unique_ptr<Shader>(new Shader("baseVert.glsl", "baseFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords"));
	projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");

	return true;
}

void Terrain::OnDestroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void Terrain::Update(float deltaTime) {

}

void Terrain::Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix) {
	glUseProgram(shader->getProgram());
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	mesh->Render();
	glEnableVertexAttribArray(0); // Disable the VAO
}