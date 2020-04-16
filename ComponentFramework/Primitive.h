#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Model.h"
#include "Shader.h"
#include "ObjLoader.h"

namespace GAME {
	class Primitive : public Model {

	public:

		Primitive(const Primitive&) = delete;
		Primitive(Primitive&&) = delete;
		Primitive& operator = (const Primitive&) = delete;
		Primitive& operator = (Primitive&&) = delete;

		Primitive(GLenum drawMode_, std::vector<Vec3> &vertices_, std::vector<Vec3> &normals, std::vector<Vec2> &uvs_);
		Primitive(std::string filePath_);
		virtual ~Primitive();


		virtual bool OnCreate();
		virtual void OnDestroy();
		virtual void Update(const float deltaTime);
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix)const;


		//Getter functions

		inline std::vector<Vec3> getVertices() const {return vertices;}

	private:

		std::vector<Vec3> vertices;

		//-------------------------------------

		Shader *shader;
		GLuint vbo;
		GLuint vao;
		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;

		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;


	};
}
#endif

