#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Abs_Entity::upload(dmat4 const& modelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat)); // transfers modelView matrix to the GPU
}

EjesRGB::EjesRGB(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::createRGBAxes(l);
}

EjesRGB::~EjesRGB()
{
	delete mMesh;
	mMesh = nullptr;
};

void
EjesRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}

//------Ejercicio3:
RegularPolygon::RegularPolygon(GLuint num, GLdouble r)
	: Abs_Entity()
{
	mMesh = Mesh::generateRegularPolygon(num, r);
}
RegularPolygon::~RegularPolygon()
{
	delete mMesh;
	mMesh = nullptr;
};
void RegularPolygon::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glColor4d(mColor.r, mColor.g, mColor.b, mColor.a);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		glColor4d(1, 1, 1, 1);
	}
}

//------Ejercicio6:
RGBTriangle::RGBTriangle(GLdouble r)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBTriangle(r);
}

//------Ejercicio14:
RGBTriangle::RGBTriangle(GLdouble r, GLdouble x, GLdouble y) :
	RGBTriangle(r)
{
	parentR = x;
	pos = dvec3(x, y, 0);
	mModelMat = translate(mModelMat, dvec3(x, y, 0));
}


void RGBTriangle::update() {
	//------Ejercicio 15:

	// Deshacemos rotacion y ponemos el triangulo en el (0.0.0).
	mModelMat = rotate(mModelMat, radians(- actualAngle), dvec3(0, 0.0, 1.0));
	mModelMat = translate(mModelMat, -pos);

	// Calculamos la nueva posicion exacta del triangulo usando las ecuaciones de la circunferencia.
	pos = dvec3(0 + parentR * glm::cos(glm::radians((360.0 / 100) * actualStep)),
		0 + parentR * glm::sin(glm::radians((360.0 / 100) * actualStep)), 0);

	// Actualizamos los parametros utilizados para marcar cuanto lleva girado el triangulo.
	// Posicion.
	actualStep++;
	if (actualStep >= 100)
	{
		actualStep = 0;
	}

	mModelMat = translate(mModelMat, pos);

	// Rotacion.
	actualAngle -= 5.0;

	if (actualAngle <= -360) {
		actualAngle = 0;
	}

	// Giramos nuevamente el triangulo.
	mModelMat = rotate(mModelMat, radians(actualAngle), dvec3(0, 0.0, 1.0));



}

RGBTriangle::~RGBTriangle()
{
	delete mMesh;
	mMesh = nullptr;
};
void RGBTriangle::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(1);
	}
}

//------Ejercicio8:
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBRectangle(w, h);
}
RGBRectangle::~RGBRectangle()
{
	delete mMesh;
	mMesh = nullptr;
};

void RGBRectangle::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(1);
	}
}

//------Ejercicio9:
Cube::Cube(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::generateCube(l);
}
Cube::~Cube()
{
	delete mMesh;
	mMesh = nullptr;
};
void Cube::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(1);
	}
}
//------Ejercicio10:
RGBCube::RGBCube(GLdouble l)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBCubeTriangles(l);
}
RGBCube::~RGBCube()
{
	delete mMesh;
	mMesh = nullptr;
};
void RGBCube::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(1);
	}
}