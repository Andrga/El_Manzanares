#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Material.h"

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
class QuadricEntity : public Abs_Entity {
public:
	explicit QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLUquadricObj* q;
};
class Sphere : public QuadricEntity {
public:
	explicit Sphere(GLdouble rr, GLfloat rrcc, GLfloat ggcc, GLfloat bbcc);
	~Sphere();
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
	GLfloat rc, gc, bc;
};
class Cylinder : public QuadricEntity {
public:
	explicit Cylinder(GLdouble bbrr, GLdouble ttrr, GLdouble hh, GLfloat rrcc, GLfloat ggcc, GLfloat bbcc);
	~Cylinder();
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble br; // Radio de la base.
	GLdouble tr; // Radio de la base superior.
	GLdouble h; // Altura.
	GLfloat rc, gc, bc; // Colores RGB.
};
class Disk : public QuadricEntity {
public:
	explicit Disk(GLdouble iirr, GLdouble oorr, GLfloat rrcc, GLfloat ggcc, GLfloat bbcc);
	~Disk();
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ir_;
	GLdouble or_;
	GLfloat rc, gc, bc;
};
class PartialDisk : public QuadricEntity {
public:
	explicit PartialDisk(GLdouble iirr, GLdouble oorr, GLdouble ssttaa, GLdouble sswwaa, GLfloat rrcc, GLfloat ggcc, GLfloat bbcc);
	~PartialDisk();
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble ir_;
	GLdouble or_;
	GLdouble sta_;
	GLdouble swa_;
	GLfloat rc, gc, bc;
};
//------Ejercicio59:
class CompoundEntity : public Abs_Entity {
public:
	explicit CompoundEntity();
	~CompoundEntity();
	void render(glm::dmat4 const& modelViewMat) const override;
	void addEntity(Abs_Entity* ae);

private:
	std::vector<Abs_Entity*> gObjects; // Vector de entidades.

};

//------Ejercicio60:
//----General:
class AdvancedTIEX_1 : public CompoundEntity {
public:
	AdvancedTIEX_1();
	~AdvancedTIEX_1() override;
	void render(glm::dmat4 const& modelViewMat) const override;
	void update() override;

private:
	QuadricEntity* body; // La esfera.
	Abs_Entity* nose; // El cilindro con el disco que sobresale hacia delante.
	QuadricEntity* cosaDeAlaAAla; // El cilindro que va de ala a ala y no se nombrar de otra forma.
	Abs_Entity* rightWing; // Ala derecha.
	Abs_Entity* leftWing; // Ala izquierda.
};
//----Ala:
class WingTIE : public Abs_Entity {
public:
	WingTIE(GLdouble x, GLdouble y, GLdouble z, GLdouble rot, bool inv, const std::string& tex);
	~WingTIE();
	void render(glm::dmat4 const& modelViewMat) const override;
	void setTexture(Texture* texture, std::string text, GLubyte alpha) const {
		texture->load(text, alpha);
	}


private:
	glm::dmat4 mMat = glm::dmat4();
	Texture* texture;
};
//---Morro:
class NoseTIE : public CompoundEntity
{
public:
	NoseTIE();
	~NoseTIE();
	void render(glm::dmat4 const& modelViewMat) const override;

private:
	Abs_Entity* cylinder; // El morro como tal que hay que cerrar.
	Abs_Entity* disk; // La tapa del cilindro.
};


//------Ejercicio64:
class IndexedBox : public Abs_Entity {
public:
	explicit IndexedBox(GLdouble l, GLfloat rrcc, GLfloat ggcc, GLfloat bbcc);
	~IndexedBox();
	void render(glm::dmat4 const& modelViewMat) const override;

private:
	std::vector<Abs_Entity*> gObjects;
	GLfloat rc, gc, bc;

};
#pragma endregion

#pragma region P5
class EntityWithMaterial : public Abs_Entity
{
protected:
	Material* material;

public:
	EntityWithMaterial();
	~EntityWithMaterial();

	void setMaterial(Material* m) { material = m; }
};

class SphereMbR : public EntityWithMaterial {
private:
	int r_, p_, m_;
	glm::dvec3* perfil;

public:
	SphereMbR(int, int, int);
	~SphereMbR();

	void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
};

class ToroidMbR : public EntityWithMaterial {
private:
	int r_, R_, p_, m_;
	glm::dvec3* perfil;

public:
	ToroidMbR(int, int, int, int);
	~ToroidMbR();

	void render(glm::dmat4 const& modelViewMat) const;
	void update() override;
};


#pragma endregion


#endif //_H_Entities_H_
