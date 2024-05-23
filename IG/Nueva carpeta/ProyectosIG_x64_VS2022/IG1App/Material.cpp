#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

//------Ejercicio74:
void Material::upload()
{
	glColorMaterial(face, GL_SPECULAR);
	glColorMaterial(face, GL_SHININESS);
	glColorMaterial(face, GL_AMBIENT);
	glColorMaterial(face, GL_DIFFUSE);
	// Ajusta caracteristicas del material
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	// Shadea el modelo
	glShadeModel(sh);
}

void Material::setCopper()
{
	ambient = { 0.25725, 0.1995, 0.0745, 1 };
	diffuse = { 0.7038, 0.27048, 0.0828, 1 };
	specular = { 0.256777, 0.137622, 0.086014, 1 };
	expF = 12.8;
}

void Material::setGold()
{
	ambient = { 0.19125, 0.0735, 0.0225, 1 };
	diffuse = { 0.75164, 0.60648, 0.22648, 1 };
	specular = { 0.628281, 0.555802, 0.366065,1 };
	expF = 51.2;
}

void Material::reset()
{
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	glMaterialfv(face, GL_AMBIENT, value_ptr(glm::fvec4(0.2, 0.2, 0.2, 1)));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(glm::fvec4(0.8, 0.8, 0.8, 1)));
	glMaterialfv(face, GL_SPECULAR, value_ptr(glm::fvec4(0.0, 0.0, 0.0, 1)));
}
