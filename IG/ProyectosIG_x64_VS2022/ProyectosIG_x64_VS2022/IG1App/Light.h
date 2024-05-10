#pragma once

#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include "Texture.h"

class Material;

class Light
{

public:
	static GLuint cont;
	GLuint id = GL_LIGHT0 + GL_MAX_LIGHTS;

	//----Atributos luminicos y geometricos de la fuente de luz.
	glm::fvec4 ambient = { 0.1, 0.1, 0.1, 1 };
	glm::fvec4 diffuse = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glm::fvec4 posDir = { 0, 0, 1, 0 };

	//------Getters:
	glm::fvec4 getAmbient() const { return ambient; }
	glm::fvec4 getDiffuse() const { return diffuse; }
	glm::fvec4 getSpecular() const { return specular; }
	glm::fvec4 getPosDir() const { return posDir; }
	//------Setters:
	void setAmbient(glm::fvec4 ambi)
	{
		ambient = ambi;
		uploadL();
	};

	void setDiffuse(glm::fvec4 diff)
	{
		diffuse = diff;
		uploadL();
	};

	void setSpecular(glm::fvec4 spec)
	{
		specular = spec;
		uploadL();
	};

	void setPosDir(glm::fvec4 psos)
	{
		posDir = psos;
		uploadL();
	};

	void setID(GLuint id_)
	{
		id = id_;
	}


	Light();

	virtual ~Light()
	{
		disable();
	}

	void uploadL() const; // Método abstracto 

	virtual void upload(const glm::dmat4& modelViewMat) const = 0;

	void disable()
	{
		if (id < GL_LIGHT0 + GL_MAX_LIGHTS)
		{
			glDisable(id);
		}
	}
	void enable() {
		if (id < GL_LIGHT0 + GL_MAX_LIGHTS)
		{
			glEnable(id);
		}
	};



};
class DirLight : public Light
{
public:
	void upload(glm::dmat4 const& modelViewMat)const override;
	void setPosDir(glm::fvec3 dir);
};

class PosLight : public Light 
{
protected:
	// Factores de atenuacion.
	GLfloat kc = 1, kl = 0, kq = 0;
public:
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setPosDir(glm::fvec3 dir);
	void setAtte(GLfloat kc, GLfloat kl, GLfloat kc);
};

class SpotLight : public PosLight {
protected:
	// Atributos del foco.
	glm::fvec4 direction = { 0, 0,-1, 0 };
	GLfloat cutoff = 180;
	GLfloat exp = 0;
public:
	SpotLight(glm::fvec3 pos = { 0, 0, 0 }) : PosLight() 
	{
		posDir = glm::fvec4(pos, 1.0);
	};
	virtual void upload(glm::dmat4 const& modelViewMat) const;
	void setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e);
};
