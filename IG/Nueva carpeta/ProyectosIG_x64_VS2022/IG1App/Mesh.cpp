#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
using namespace std;
using namespace glm;

void
Mesh::draw() const
{
	glDrawArrays(
		mPrimitive,
		0,
		size()); // primitive graphic, first index and number of elements to be rendered
}

void
Mesh::render() const
{
	if (vVertices.size() > 0) { // transfer data
		// transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(
			3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
		// each coordinate, stride, pointer
		if (vColors.size() > 0) {             // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(
				4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
			// each component, stride, pointer
		}

		draw();

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

Mesh*
Mesh::createRGBAxes(GLdouble l)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINES;

	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// X axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(l, 0.0, 0.0);
	// Y axis vertices
	mesh->vVertices.emplace_back(0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, l, 0.0);
	// Z axis vertices
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vVertices.emplace_back(0.0, 0.0, l);

	mesh->vColors.reserve(mesh->mNumVertices);
	// X axis color: red  (Alpha = 1 : fully opaque)
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// Y axis color: green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// Z axis color: blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

//------Ejercicio 2:
Mesh* Mesh::generateRegularPolygon(GLuint num, GLdouble r) {// Generate a regular polygon
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = num;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble x, y;

	//mesh->vVertices.emplace_back(r * glm::cos(glm::radians((90 / num))), r * glm::cos(glm::radians((90 / num))), 0.0);

	for (int i = 0; i < num; i++)
	{
		x = 0 + r * glm::cos(glm::radians(90.0) + glm::radians((360.0 / num) * i));
		y = 0 + r * glm::sin(glm::radians(90.0) + glm::radians((360.0 / num) * i));
		mesh->vVertices.emplace_back(x, y, 0.0);
		//mesh->vVertices.emplace_back(r * cos(radians((360.0 / num) * i)), r * sin(radians((360.0 / num) * i)), 0.0); //Se supone que pone el resto de v�rtices

	}

	return mesh;
}
//------Ejercicio6:
Mesh* Mesh::generateRGBTriangle(GLdouble r) { // Genera un triangulo RGB:
	Mesh* mesh = new Mesh();

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE); // Ejercicio7.

	mesh->mNumVertices = 3;
	mesh->vVertices.reserve(mesh->mNumVertices);

	GLdouble x, y;

	//mesh->vVertices.emplace_back(r * glm::cos(glm::radians((90 / num))), r * glm::cos(glm::radians((90 / num))), 0.0);

	for (int i = 0; i < 3; i++)
	{
		x = 0 + r * glm::cos(glm::radians(90.0) + glm::radians((360.0 / 3) * i));
		y = 0 + r * glm::sin(glm::radians(90.0) + glm::radians((360.0 / 3) * i));
		mesh->vVertices.emplace_back(x, y, 1.0);
		//mesh->vVertices.emplace_back(r * cos(radians((360.0 / num) * i)), r * sin(radians((360.0 / num) * i)), 0.0); //Se supone que pone el resto de v�rtices

	}
	mesh->vColors.reserve(mesh->mNumVertices);
	// red
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	// green
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	// blue
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);


	return mesh;
}
//------Ejercicio8:
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h) { // Genera un rectangulo:
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(h / 2, -w / 2, 0); //1
	mesh->vVertices.emplace_back(-h / 2, -w / 2, 0); //3
	mesh->vVertices.emplace_back(h / 2, w / 2, 0); //2
	mesh->vVertices.emplace_back(-h / 2, w / 2, 0); //4

	return mesh;
}
//------Ejercicio8:
Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h) { // Genera un rectangulo:
	Mesh* mesh = generateRectangle(w, h);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);


	mesh->vColors.reserve(mesh->mNumVertices);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); // Azul.
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // Verde.
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // Verde.
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // Rojo.

	return mesh;
}