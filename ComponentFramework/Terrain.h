#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"
#include "Shader.h"

#include <memory>
#include <utility>
#include <map>

using namespace GAME;

//Created by Noah.C

class Terrain {

	/*The idea of the Terrain is to create a bunch on
	vertex points and mesh them together to create a floor.
	This will allow the generator to place vertex points
	above or below the origin on the y axis, creating the 
	difference in height for hills and valleys.*/

	///Terrain doesn't really inherit from anything because it's kind of
	///it's own unique thing. The terrain is an object but it doesn't
	///behave like other objects.

private:

	int width;
	int length;

	//std::pair<Vec2, float> vertex;
	//std::map<Vec2, float> heightMap;

	std::unique_ptr<std::map<Vec2, float>> heightMap;

	std::unique_ptr<Mesh> mesh;
	std::unique_ptr<Shader> shader;
	//Mesh* mesh;
	//Shader *shader;

	Matrix4 modelMatrix;

	GLint projectionMatrixID;
	GLint modelViewMatrixID;
	GLint normalMatrixID;

	GLint verticiesID;
	GLint normalsID;
	GLint uvCoordsID;

	Sphere bounding;

	GLuint vbo;
	GLuint vao;

public:

	Terrain(int width_, int length_);
	~Terrain();

	bool OnCreate();
	void OnDestroy();
	void Update(float deltaTime);
	void Render(const Matrix4& projectionMatrix, const Matrix4& viewMatrix, const Matrix3& normalMatrix);

	//inline void setHeight(const int x_, const int z_, float newy_) { vertexPoint[z_][x_] = newy_; } //Set the new height for a given point

	inline int getLength() const { return length; } //Get the length of the terrain
	inline int getWidth() const { return width; } //Get the width of the terrain
	//inline const float getHeight(const int x_, const int z_) { return vertexPoint[z_][x_]; } //Get the height of a point on the terrain
	//inline const Vec3 getNormal(const int x_, const int z_) { return normals[z_][x_]; } //Get the normal of a point on the terrain

};

#endif // !TERRAIN_H

