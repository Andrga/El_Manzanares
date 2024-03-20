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
#pragma region P1
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
		glPolygonMode(GL_FRONT, GL_FILL);
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
	mModelMat = rotate(mModelMat, radians(-actualAngle), dvec3(0, 0.0, 1.0));
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
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL); // Ejercicio7.

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(1);
	}
}
//------Ejercicio8:
RGBRectangle::RGBRectangle(GLdouble w, GLdouble h, GLdouble z)
	: Abs_Entity()
{
	mMesh = Mesh::generateRGBRectangle(w, h, z);
}
RGBRectangle::~RGBRectangle()
{
	delete mMesh;
	mMesh = nullptr;
};
void RGBRectangle::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);

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
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_POINT);

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
	actualAngle = 0;
	rotAxe = dvec3(1.0, 0.0, 0.0);
}
RGBCube::~RGBCube()
{
	delete mMesh;
	mMesh = nullptr;
};
//-------Ejercicio17:
void RGBCube::update() {

	if (actualAngle >= 180) {
		actualAngle = 0;

		if (rotAxe == dvec3(1.0, 0.0, 0.0))
		{
			rotAxe = dvec3(0.0, 0.0, 1.0);
		}
		else if (rotAxe == dvec3(0.0, 0.0, 1.0)) {

			rotAxe = dvec3(0.0, 1.0, 0.0);
		}
		else if (rotAxe == dvec3(0.0, 1.0, 0.0)) {

			rotAxe = dvec3(1.0, 0.0, 0.0);
		}
	}

	mModelMat = rotate(mModelMat, radians(1.0), rotAxe);
	actualAngle += 1;
}
void RGBCube::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		glPolygonMode(GL_FRONT, GL_POINT);
		glPolygonMode(GL_BACK, GL_FILL);

		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(1);
	}
}
#pragma endregion

#pragma region P2
//------Ejercicio18:
Ground::Ground(GLdouble w, GLdouble d, std::string t)
	: Abs_Entity()
{
	mMesh = Mesh::generateRectangleTexCor(w, d);
	mModelMat = rotate(mModelMat, radians(90.0), dvec3(0.0, 1.0, 0.0));

	texture = new Texture();
	setTexture(t);
}
//------Ejercicio20:
Ground::Ground(GLdouble w, GLdouble d, GLuint rw, GLuint rh, std::string t)
	: Abs_Entity()
{
	mMesh = Mesh::generateRectangleTexCor(w, d, rw, rh);
	mModelMat = rotate(mModelMat, radians(90.0), dvec3(0.0, 1.0, 0.0)) *
		rotate(mModelMat, radians(180.0), dvec3(1.0, 0.0, 0.0));

	texture = new Texture();
	setTexture(t);
}
Ground::~Ground()
{
	delete mMesh;
	mMesh = nullptr;
	delete texture;
	texture = nullptr;
};
void Ground::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		texture->bind(GL_MODULATE); // Modulate mezcla el color con la textura
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		texture->unbind();
	}
}
//------Ejercicio22:
BoxOutline::BoxOutline(GLdouble lenght)
	:Abs_Entity()
{
	mMesh = Mesh::generateBoxOutlineTexCor(lenght);
}
BoxOutline::BoxOutline(GLdouble lenght, std::string t)
	:BoxOutline(lenght)
{
	outTexture = new Texture();
	setTexture(outTexture, t);
	setTexture(intTexture, t);
}
BoxOutline::BoxOutline(GLdouble lenght, std::string iT, std::string oT)
	:BoxOutline(lenght)
{

	outTexture = new Texture();
	intTexture = new Texture();

	setTexture(intTexture, oT);
	setTexture(outTexture, iT);
}
BoxOutline::~BoxOutline()
{
	delete mMesh;
	mMesh = nullptr;
	delete outTexture;
	outTexture = nullptr;
	delete intTexture;
	intTexture = nullptr;
}
void BoxOutline::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		glEnable(GL_CULL_FACE);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		outTexture->bind(GL_MODULATE); // Modulate mezcla el color con la textura
		glCullFace(GL_BACK);
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		outTexture->unbind();
		glEnable(GL_CULL_FACE);

		intTexture->bind(GL_MODULATE); // Modulate mezcla el color con la textura
		glCullFace(GL_FRONT);
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		intTexture->unbind();

		glDisable(GL_CULL_FACE);
	}
}
//------Ejercicio26:
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h) : Abs_Entity()
{
	mMesh = Mesh::generateStar3D(re, np, h);
}
Star3D::Star3D(GLdouble re, GLuint np, GLdouble h, std::string t)
//:Star3D(re, np, h) // Me estas tocando los cojones somos tontos tontos claro que no hacia texturas porque no llamabamos al que hacia texturas...
{

	mMesh = Mesh::generateStar3DTexCor(re, np, h); // Hay que hacer esto.

	mModelMat = translate(dmat4(1), dvec3(0, 200, 0));
	texture = new Texture;

	setTexture(texture, t);
}
Star3D::~Star3D()
{
	delete mMesh;
	mMesh = nullptr;
	delete texture;
	texture = nullptr;
}
void Star3D::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		glDisable(GL_CULL_FACE);
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		texture->bind(GL_REPLACE); // Modulate mezcla el color con la textura
		upload(aMat);
		glLineWidth(2);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mMesh->render();
		// Se puedo usar el escalado negativo.
		dmat4 aMat2 = aMat * glm::rotate(dmat4(1), glm::radians(180.0), dvec3(1.0, 0.0, 0.0)); // Rotamos la matriz y la volvemos a renderizar.
		glLineWidth(2);
		upload(aMat2);
		mMesh->render();
		texture->unbind();

	}
}
//----Ejercicio27:
void Star3D::update() {
	angle++;

	mModelMat = translate(dmat4(1), dvec3(0, 200, 0))
		* rotate(dmat4(1), radians(angle), dvec3(0.0, 0.0, 1.0)) // Movimiento en el eje Z.
		* rotate(dmat4(1), radians(angle), dvec3(0.0, 1.0, 0.0)); // Movimiento en el eje Y.

}
//------Ejercicio31:
GlassParapet::GlassParapet(GLdouble lenght)
	:Abs_Entity()
{
	mMesh = Mesh::generateBoxOutlineTexCor(lenght);
}
GlassParapet::GlassParapet(GLdouble lenght, std::string t)
	:GlassParapet(lenght)
{
	texture = new Texture();
	setTexture(texture, t, 100);
}
GlassParapet::~GlassParapet()
{
	delete mMesh;
	mMesh = nullptr;
	delete texture;
	texture = nullptr;
}
// NOTA: Renderizar primero los objetos opacos y despues los translucidos para que renderice las partes transparentes bien.
void GlassParapet::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		//glEnable(GL_BLEND);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		texture->bind(GL_MODULATE);// GL_REPLACE, GL_MODULATE, GL_ADD
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		texture->unbind();
	}
}

Photo::Photo(GLdouble lenght)
	:Abs_Entity()
{
	texture = new Texture();
	texture->loadColorBuffer(800, 600);

	mMesh = Mesh::generateRectangleTexCor(100, 66.66);
	mModelMat = rotate(mModelMat, radians(180.0), dvec3(1.0, 0.0, 0.0)) // rotacion
		* translate(mModelMat, dvec3(0.0, -1.0, 0.0));

	//setTexture(texture, , 100);
}
Photo::~Photo()
{
	delete mMesh;
	mMesh = nullptr;
	delete texture;
	texture = nullptr;
}

void Photo::render(dmat4 const& modelViewMat)const
{
	if (mMesh != nullptr) {

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		texture->bind(GL_REPLACE);// GL_REPLACE, GL_MODULATE, GL_ADD
		dmat4 aMat = modelViewMat * mModelMat; // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
		texture->unbind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	}
}

void Photo::update()
{
	texture->loadColorBuffer(800, 600, GL_BACK);
}
#pragma endregion

#pragma region P3

#pragma endregion
