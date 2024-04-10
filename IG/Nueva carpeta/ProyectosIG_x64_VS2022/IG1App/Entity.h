#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
		: mModelMat(1.0), mColor(1) {}; // 4x4 identity matrix
	virtual ~Abs_Entity() = default;

	Abs_Entity(const Abs_Entity& e) = delete;            // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete; // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0; // abstract method

	glm::dvec4 const& getColor() { return mColor; } // Getter color
	void setColor(glm::dvec4 const& col) { mColor = col; } // Getter color

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//------Ejercicio13:
	virtual void update() {};

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix
	glm::dvec4 mColor; //Color de la mesh
	GLdouble actualAngle; // Angulo
	glm::dvec3 pos; // Posicion

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
};

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	void render(glm::dmat4 const& modelViewMat) const;
};
#pragma region P1
//------Ejercicio3:
class RegularPolygon : public Abs_Entity
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r);
	~RegularPolygon();
	void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio6:
class RGBTriangle : public Abs_Entity
{
public:
	explicit RGBTriangle(GLdouble r);
	//------Ejercicio14:
	explicit RGBTriangle(GLdouble r, GLdouble x, GLdouble y);

	void update() override;

	~RGBTriangle();
	void render(glm::dmat4 const& modelViewMat) const;

private:
	//------Ejercicio15:
	GLdouble angle = 5.0;

	GLdouble parentR;
	GLuint actualStep = 0;
};
//------Ejercicio8:
class RGBRectangle : public Abs_Entity
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h, GLdouble z);
	~RGBRectangle();
	void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio9:
class Cube : public Abs_Entity
{
public:
	explicit Cube(GLdouble l);
	~Cube();
	void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio10:
class RGBCube : public Abs_Entity
{
public:
	explicit RGBCube(GLdouble l);
	~RGBCube();

	//------Ejercicio17:
	void update() override;
	void render(glm::dmat4 const& modelViewMat) const;

private:
	glm::dvec3 rotAxe;
	GLdouble actualAngle = 0;

};
#pragma endregion

#pragma region P2
//------Ejercicio18:
class Ground : public Abs_Entity
{
private:
	Texture* texture;

public:
	explicit Ground(GLdouble w, GLdouble d, std::string t);
	explicit Ground(GLdouble w, GLdouble d, GLuint rw, GLuint rh, std::string t);
	~Ground();
	void render(glm::dmat4 const& modelViewMat) const;
	void setTexture(std::string text) const {
		texture->load(text, 255);
	}
};

//------Ejercicio22:
class BoxOutline : public Abs_Entity
{
private:
	Texture* outTexture;
	Texture* intTexture;

public:
	explicit BoxOutline(GLdouble lenght);
	explicit BoxOutline(GLdouble lenght, std::string t);
	explicit BoxOutline(GLdouble lenght, std::string iT, std::string oT);
	~BoxOutline();
	void render(glm::dmat4 const& modelViewMat) const;
	void setTexture(Texture* texture, std::string text) const {
		texture->load(text, 255);
	}
};

//------Ejercicio26:
class Star3D : public Abs_Entity
{
private:
	Texture* texture;
	GLdouble angle = 0;

public:
	explicit Star3D(GLdouble re, GLuint np, GLdouble h);
	Star3D(GLdouble re, GLuint np, GLdouble h, std::string t);
	~Star3D();
	void render(glm::dmat4 const& modelViewMat) const;
	void setTexture(Texture* texture, std::string text) const {
		texture->load(text, 255);
	}
	void update() override; // Ejercicio27.
};
//------Ejercicio31:
class GlassParapet : public Abs_Entity
{
private:
	Texture* texture;

public:
	explicit GlassParapet(GLdouble lenght);
	explicit GlassParapet(GLdouble lenght, std::string t);
	~GlassParapet();
	void render(glm::dmat4 const& modelViewMat) const;
	void setTexture(Texture* texture, std::string text, GLubyte alpha) const {
		texture->load(text, alpha);
	}
};
//------Ejercicio36:
class Photo : public Abs_Entity
{
private:
	Texture* texture;

public: 
	explicit Photo(GLdouble lenght);
	~Photo();
	void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
	void setTexture(Texture* texture, std::string text, GLubyte alpha) const {
		texture->load(text, alpha);
	}
};
#pragma endregion

#pragma region P4
//------Ejercicio57:
class QuadricEntity :Abs_Entity {
public:
	explicit QuadricEntity();
	~QuadricEntity();
	void render(glm::dmat4 const& modelViewMat) const;
};
#pragma endregion

#endif //_H_Entities_H_
