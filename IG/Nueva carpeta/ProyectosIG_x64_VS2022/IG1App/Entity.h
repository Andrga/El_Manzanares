#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"

class Abs_Entity // abstract class
{
public:
	Abs_Entity()
	  : mModelMat(1.0), mColor(1){}; // 4x4 identity matrix
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
	void update();

protected:
	Mesh* mMesh = nullptr; // the mesh
	glm::dmat4 mModelMat;  // modeling matrix
	glm::dvec4 mColor; //Color de la mesh

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
};

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio3:
class RegularPolygon : public Abs_Entity
{
public:
	explicit RegularPolygon(GLuint num, GLdouble r);
	~RegularPolygon();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio6:
class RGBTriangle : public Abs_Entity
{
public:
	explicit RGBTriangle( GLdouble r);
	~RGBTriangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio8:
class RGBRectangle : public Abs_Entity
{
public:
	explicit RGBRectangle(GLdouble w, GLdouble h);
	~RGBRectangle();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio9:
class Cube : public Abs_Entity
{
public:
	explicit Cube(GLdouble l);
	~Cube();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
//------Ejercicio10:
class RGBCube : public Abs_Entity
{
public:
	explicit RGBCube(GLdouble l);
	~RGBCube();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};
#endif //_H_Entities_H_
