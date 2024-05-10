#include "Material.h"
#include <glm/gtc/type_ptr.hpp>

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

	//PAIGRO AQUI
}

void Material::setGolden()
{
}

void Material::reset()
{
}
