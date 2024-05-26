#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
#include <iostream>
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

		if (vTexCoords.size() > 0)
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());

		}
		//----Ejercicio61:
		if (vNormals.size() > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, vNormals.data());
		}
		draw();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
	}
}

Mesh* Mesh::createRGBAxes(GLdouble l)
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

// Region con los apartados de la P1:
#pragma region P1
//------Ejercicio2:
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

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_LINE); // Ejercicio7.

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
Mesh* Mesh::generateRectangle(GLdouble w, GLdouble h, GLdouble d) { // Genera un rectangulo:
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);

	//mesh->vVertices.emplace_back(w / 2, -h / 2, -d / 2); //1
	//mesh->vVertices.emplace_back(-w / 2, -h / 2, d / 2); //3
	//mesh->vVertices.emplace_back(w / 2, h / 2, -d / 2); //2
	//mesh->vVertices.emplace_back(-w / 2, h / 2, d / 2); //4

	mesh->vVertices.emplace_back(-w / 2, -h / 2, -d / 2); //1
	mesh->vVertices.emplace_back(-w / 2, h / 2, d / 2); //3
	mesh->vVertices.emplace_back(w / 2, -h / 2, -d / 2); //2
	mesh->vVertices.emplace_back(w / 2, h / 2, d / 2); //4

	return mesh;
}
Mesh* Mesh::generateRGBRectangle(GLdouble w, GLdouble h, GLdouble z) { // Genera un rectangulo:
	Mesh* mesh = generateRectangle(w, h, z);

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_LINE);

	mesh->vVertices.reserve(mesh->mNumVertices);


	mesh->vColors.reserve(mesh->mNumVertices);
	//mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); // Azul.
	//mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // Verde.
	//mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // Verde.
	//mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // Rojo.

	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0); // Blanco.
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0); // Blanco.
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0); // Blanco.
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0); // Blanco.

	return mesh;
}
//------Ejercicio9.
Mesh* Mesh::generateCube(GLdouble l) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_POINT);

	GLdouble m = l / 2;

	mesh->mNumVertices = 14;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// colocamos los vertices en sentido anti horario
	mesh->vVertices.emplace_back(-m, -m, -m); // 4.
	mesh->vVertices.emplace_back(m, -m, -m); // 3.
	mesh->vVertices.emplace_back(-m, -m, m); // 2.
	mesh->vVertices.emplace_back(m, -m, m); // 1.
	mesh->vVertices.emplace_back(m, m, m); // 5.
	mesh->vVertices.push_back(mesh->vVertices[1]); // 3.
	mesh->vVertices.emplace_back(m, m, -m); // 8.
	mesh->vVertices.emplace_back(-m, m, -m); // 7.
	mesh->vVertices.push_back(mesh->vVertices[4]); // 5.
	mesh->vVertices.emplace_back(-m, m, m); // 6.
	mesh->vVertices.push_back(mesh->vVertices[2]); // 2.
	mesh->vVertices.push_back(mesh->vVertices[7]); // 7.
	mesh->vVertices.push_back(mesh->vVertices[0]); // 4.
	mesh->vVertices.push_back(mesh->vVertices[1]); // 3.


	/*
	mesh->vVertices.push_back(mesh->vVertices[x]); // Repetidos.
	mesh->vVertices.emplace_back(l, -l, l); // 1.
	mesh->vVertices.emplace_back(-l, -l, l); // 2.
	mesh->vVertices.emplace_back(l, -l, -l); // 3.
	mesh->vVertices.emplace_back(-l, -l, -l); // 4.
	mesh->vVertices.emplace_back(l, l, l); // 5.
	mesh->vVertices.emplace_back(-l, l, l); // 6.
	mesh->vVertices.emplace_back(-l, l, -l); // 7.
	mesh->vVertices.emplace_back(l, l, -l); // 8.
	*/

	return mesh;
}
//------Ejercicio10:
Mesh* Mesh::generateRGBCubeTriangles(GLdouble length) {

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLES;

	//glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_BACK, GL_POINT);

	GLdouble m = length / 2;

	mesh->mNumVertices = 36;

	mesh->vVertices.reserve(mesh->mNumVertices);

	// Cara abajo:
	/*0*/mesh->vVertices.emplace_back(-m, -m, -m); // 1.
	mesh->vVertices.emplace_back(m, -m, m); // 4.
	mesh->vVertices.emplace_back(-m, -m, m); // 3.

	mesh->vVertices.push_back(mesh->vVertices[0]); // 1.
	mesh->vVertices.emplace_back(m, -m, -m); // 2.
	mesh->vVertices.push_back(mesh->vVertices[1]); // 4

	// Cara arriba:
	/*6*/mesh->vVertices.emplace_back(-m, m, -m); // 5.
	mesh->vVertices.emplace_back(-m, m, m); // 7.
	mesh->vVertices.emplace_back(m, m, m); // 8.

	mesh->vVertices.push_back(mesh->vVertices[6]); // 5.
	mesh->vVertices.push_back(mesh->vVertices[8]); // 8
	mesh->vVertices.emplace_back(m, m, -m); // 6.

	// Cara derecha:
	/*12*/mesh->vVertices.emplace_back(m, m, m); // 8.
	mesh->vVertices.emplace_back(m, -m, -m); // 2.
	mesh->vVertices.emplace_back(m, m, -m); // 6.

	mesh->vVertices.push_back(mesh->vVertices[12]); // 8
	mesh->vVertices.emplace_back(m, -m, m); // 4.
	mesh->vVertices.push_back(mesh->vVertices[13]); // 2

	// Cara izquierda:
	/*18*/mesh->vVertices.emplace_back(-m, m, m); // 7.
	mesh->vVertices.emplace_back(-m, m, -m); // 5.
	mesh->vVertices.emplace_back(-m, -m, m); // 3.

	mesh->vVertices.push_back(mesh->vVertices[19]); // 5
	mesh->vVertices.emplace_back(-m, -m, -m); // 1.
	mesh->vVertices.push_back(mesh->vVertices[20]); // 3

	// Cara atras:
	/*24*/mesh->vVertices.emplace_back(-m, m, -m); // 5.
	mesh->vVertices.emplace_back(m, m, -m); // 6.
	mesh->vVertices.emplace_back(-m, -m, -m); // 1.

	mesh->vVertices.push_back(mesh->vVertices[25]); // 6
	mesh->vVertices.emplace_back(m, -m, -m); // 2.
	mesh->vVertices.push_back(mesh->vVertices[26]); // 1

	// Cara alante:
	/*30*/mesh->vVertices.emplace_back(-m, m, m); // 7.
	mesh->vVertices.emplace_back(m, -m, m); // 4.
	mesh->vVertices.emplace_back(m, m, m); // 8.

	mesh->vVertices.push_back(mesh->vVertices[30]); // 7
	mesh->vVertices.emplace_back(-m, -m, m); // 3.
	mesh->vVertices.push_back(mesh->vVertices[31]); // 4


	mesh->vColors.reserve(mesh->mNumVertices);

	for (int i = 0; i < mesh->mNumVertices / 3; i++)
	{
		mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); // Azul.
	}
	for (int i = 0; i < mesh->mNumVertices / 3; i++)
	{
		mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); // Verde.
	}
	for (int i = 0; i < mesh->mNumVertices / 3; i++)
	{
		mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); // Rojo.
	}

	return mesh;
}
#pragma endregion
// Region con los apartados de la P2:
#pragma region P2
// Ejercicio19.
Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h) {
	auto m = generateRectangle(w, 0, h);
	m->vTexCoords.reserve(m->mNumVertices);

	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(1, 0);
	m->vTexCoords.emplace_back(0, 1);
	m->vTexCoords.emplace_back(1, 1);
	return m;
}
//------Ejercicio20
Mesh* Mesh::generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
	auto m = generateRectangle(w, 0, h);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m->vTexCoords.reserve(m->mNumVertices);

	m->vTexCoords.emplace_back(0, 0);
	m->vTexCoords.emplace_back(rw, 0);
	m->vTexCoords.emplace_back(0, rh);
	m->vTexCoords.emplace_back(rw, rh);

	return m;
}
//------Ejercicio22
Mesh* Mesh::generateBoxOutline(GLdouble length) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLdouble m = length / 2;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(-m, m, -m); // 1.
	mesh->vVertices.emplace_back(-m, -m, -m); // 2.
	mesh->vVertices.emplace_back(-m, m, m); // 3.
	mesh->vVertices.emplace_back(-m, -m, m); // 4.
	mesh->vVertices.emplace_back(m, m, m); // 5.
	mesh->vVertices.emplace_back(m, -m, m); // 6.
	mesh->vVertices.emplace_back(m, m, -m); // 7.
	mesh->vVertices.emplace_back(m, -m, -m); // 8.
	mesh->vVertices.push_back(mesh->vVertices[0]); // 1.
	mesh->vVertices.push_back(mesh->vVertices[1]); // 2.

	return mesh;
}
//------Ejercicio 23:
Mesh* Mesh::generateBoxOutlineTexCor(GLdouble longitud) {
	auto m = generateBoxOutline(longitud);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m->vTexCoords.reserve(m->mNumVertices);

	for (int i = 0; i < 4; i++)
	{
		m->vTexCoords.emplace_back(1, 0);
		m->vTexCoords.emplace_back(1, 1);
		m->vTexCoords.emplace_back(0, 0);
		m->vTexCoords.emplace_back(0, 1);
	}

	return m;
}
//------Ejercicio 25:
Mesh* Mesh::generateStar3D(GLdouble re, GLuint np, GLdouble h) {
	Mesh* mesh = new Mesh();

	np *= 2;

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mesh->mNumVertices = np + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);

	mesh->vVertices.emplace_back(0, 0, 0);

	GLdouble x, y, r = re;

	//mesh->vVertices.emplace_back(r * glm::cos(glm::radians((90 / num))), r * glm::cos(glm::radians((90 / num))), 0.0);

	for (int i = 0; i < np; i++)
	{
		i % 2 == 0 ? r = re : r = (re / 2);

		x = 0 + r * glm::cos(glm::radians((360.0 / (np)) * i));
		y = 0 + r * glm::sin(glm::radians((360.0 / (np)) * i));

		mesh->vVertices.emplace_back(x, y, h);
	}

	mesh->vVertices.push_back(mesh->vVertices[1]); // 1.

	return mesh;
}
//------Ejercicio28:
Mesh* Mesh::generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h) {
	auto m = generateStar3D(re, np, h);

	m->vTexCoords.reserve(m->mNumVertices);

	m->vTexCoords.emplace_back(0.5, 0.5);

	for (int i = 0; i < 4; i++)
	{
		m->vTexCoords.emplace_back(0, 0);
		m->vTexCoords.emplace_back(0, 0.5);
		m->vTexCoords.emplace_back(0, 0);
		m->vTexCoords.emplace_back(0.5, 0);
	}
	m->vTexCoords.emplace_back(0, 0);

	return m;
}


#pragma endregion

//Region con los apartados de la P4:
#pragma region P4
//------Ejercicio60:
Mesh* Mesh::generateTIEWing(GLdouble h1, GLdouble h2, GLdouble d)
{
	auto* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;
	mesh->mNumVertices = 8; // Son tres cuadrados unidos, 8 vertices.
	mesh->vVertices.reserve(mesh->mNumVertices);


	mesh->vVertices.emplace_back(h1, d, h2); // V0.
	mesh->vVertices.emplace_back(h1, -d, h2); // V1.
	mesh->vVertices.emplace_back(h2, d, 0); // V2.
	mesh->vVertices.emplace_back(h2, -d, 0); // V3.
	mesh->vVertices.emplace_back(-h2, d, 0); // V4.
	mesh->vVertices.emplace_back(-h2, -d, 0); // V5.
	mesh->vVertices.emplace_back(-h1, d, h2); // V6.
	mesh->vVertices.emplace_back(-h1, -d, h2); // V7.

	mesh->vTexCoords.reserve(4);

	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(1, 0);
	mesh->vTexCoords.emplace_back(0, 1);
	mesh->vTexCoords.emplace_back(1, 1);

	return mesh;
}


IndexMesh::~IndexMesh()
{
}

IndexMesh* IndexMesh::generateIndexedBox(GLdouble l)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mNumVertices = 8;

	GLdouble s = l / 2;
	// Aniade los 8 vertices del cubo a la mesh
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(-s, s, -s);		// v0
	mesh->vVertices.emplace_back(s, s, -s);		// v1
	mesh->vVertices.emplace_back(s, -s, -s);		// v2
	mesh->vVertices.emplace_back(-s, -s, -s);	// v3
	mesh->vVertices.emplace_back(-s, s, s);		// v4
	mesh->vVertices.emplace_back(s, s, s);		// v5
	mesh->vVertices.emplace_back(s, -s, s);		// v6
	mesh->vVertices.emplace_back(-s, -s, s);		// v7

	// Indices para la creacion de primitivas
	mesh->mNumIndexes = 36;
	mesh->vIndexes = new GLuint[mesh->mNumIndexes];

	GLuint arr[36] = {
		// Laterales
		0,2,1,
		2,0,3,
		6,2,1,
		6,1,5,
		5,7,6,
		7,5,4,
		4,3,7,
		3,4,0,

		// Tapas
		0,5,1,
		0,4,5,
		3,6,2,
		3,7,6
	};

	for (int i = 0; i < mesh->mNumIndexes; i++) {

		mesh->vIndexes[i] = arr[i];
	}

	mesh->vCaras.resize(mesh->mNumIndexes / VERTEX_CARA);
	for (int i = 0; i < mesh->mNumVertices / VERTEX_CARA; i++)
	{
		mesh->vCaras[i].vec1 = mesh->vVertices[mesh->vIndexes[i * VERTEX_CARA]];
		mesh->vCaras[i].id1 = mesh->vIndexes[i * VERTEX_CARA];

		mesh->vCaras[i].vec2 = mesh->vVertices[mesh->vIndexes[(i * VERTEX_CARA) + 1]];
		mesh->vCaras[i].id2 = mesh->vIndexes[(i * VERTEX_CARA) + 1];

		mesh->vCaras[i].vec3 = mesh->vVertices[mesh->vIndexes[(i * VERTEX_CARA) + 2]];
		mesh->vCaras[i].id3 = mesh->vIndexes[(i * VERTEX_CARA) + 2];
	}

	mesh->buildNormalVectors();

	return mesh;
}


// --------- METODO SUPER IMPORTANTE PARA GENERAL LAS NORMALES ---------
void IndexMesh::buildNormalVectors()
{
	vNormals.resize(mNumIndexes);
	std::vector<glm::dvec3> vAuxNormals = vNormals; // vector auxiliar

	GLuint a = mNumIndexes / 3;

	// Newell
	for (int i = 0; i < a; i++)
	{
		//std::cout << nIndexes[(i * 3)] << std::endl;

		dvec3 v0 = vVertices[vIndexes[(i * 3)]];
		dvec3 v1 = vVertices[vIndexes[((i * 3) + 1)]];
		dvec3 v2 = vVertices[vIndexes[((i * 3) + 2)]];

		glm::dvec3 v = v1 - v0;
		glm::dvec3 w = v2 - v0;
		const glm::dvec3 n = normalize(cross(v, w));

		vAuxNormals[vIndexes[i * 3]] += n;
		vAuxNormals[vIndexes[i * 3 + 1]] += n;
		vAuxNormals[vIndexes[i * 3 + 2]] += n;
	}

	for (int i = 0; i < mNumVertices; i++) {
		vNormals[i] = normalize(vAuxNormals[i]);
	}

}

void IndexMesh::render() const
{
	if (vVertices.empty()) return;
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(
		3, GL_DOUBLE, 0, vVertices.data()); // number of coordinates per vertex, type of
	// each coordinate, stride, pointer

	/// si tiene vertices de color
	if (!vColors.empty())
	{
		// transfer colors
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(
			4, GL_DOUBLE, 0, vColors.data()); // components number (rgba=4), type of
		// each component, stride, pointer
	}

	/// si tiene vertices de textura
	if (!vTexCoords.empty())
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
	}

	if (!vNormals.empty())
	{
		//glEnable(GL_NORMALIZE);
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, vNormals.data());
	}
	if (vIndexes != nullptr)
	{
		glEnableClientState(GL_INDEX_ARRAY);
		glIndexPointer(GL_UNSIGNED_INT, 0, vIndexes);
	}

	glColorMaterial(GL_FRONT_AND_BACK, GL_FILL);
	draw();
	glDisableClientState(GL_INDEX_ARRAY);

	//glDisable(GL_NORMALIZE);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void IndexMesh::draw() const
{
	//------Ejercicio62:
	// glDrawArrays ( GL_TRIANGLES , 0 , numVertices ); antes se usaba esto para renderizar

	glDrawElements(mPrimitive, mNumIndexes, GL_UNSIGNED_INT, vIndexes);
}

#pragma endregion

#pragma region P5
//------Ejercicio69:
MbR::MbR(int perPoi, int nRot, glm::dvec3* per) : mPerfilPoints(perPoi), nRotations(nRot), perfil(per)
{

}
MbR::~MbR()
{

}

// mm (numero de vertices del perfl)
// nn (numero de rotaciones)
// per (perfil)
// angle (angulo hasta el que se hace la revolucion)
MbR* MbR::generaIndexMbR(int mm, int nn, glm::dvec3* per, int angle)
{
	MbR* m = new MbR(mm, nn, per);

	m->mPrimitive = GL_TRIANGLES;		//Primitiva
	m->mNumVertices = nn * mm;

	m->vVertices.reserve(m->mNumVertices);
	m->vNormals.reserve(m->mNumVertices);

	// reserva vertices en un array auxiliar
	dvec3* vs = new dvec3[m->mNumVertices];

	// aniade los vertices a la malla, (i indica la rotacion que se va a generar, j indica el vertice que se esta creando)
	for (int i = 0; i < nn; i++)
	{
		// cosas de la ecuacion de la circunferencia y trigonometria
		// angle hace que no se complete la rotacion en 360 siempre
		GLdouble theta = i * angle / nn;
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));

		for (int j = 0; j < mm; j++)
		{
			GLdouble z = -s * per[j].x + c * per[j].z;
			GLdouble x = c * per[j].x + s * per[j].z;

			// ultimo vertice creado
			int indice = i * mm + j;

			// aniadimos el vertice
			vs[indice] = dvec3(x, per[j].y, z);
		}
	}

	// aniadimos los vertices creados a la malla
	for (int i = 0; i < m->mNumVertices; i++)
	{
		m->vVertices.emplace_back(vs[i]);
	}
	// borramos el vector auxiliar
	delete[] vs;

	// INDICE SUPERIOR QUE RECORRE EL ARRAY DE INDICES DE LA MALLA
	int indiceMayor = 0;
	m->mNumIndexes = m->mNumVertices * 6;
	m->vIndexes = new GLuint[m->mNumIndexes];

	// Inicializamos nIndexes a 0
	for (int i = 0; i < m->mNumVertices * 6; i++)
	{
		m->vIndexes[i] = 0;
	}

	// calculamos los indices de las caras
	for (int i = 0; i < nn; i++)
	{
		for (int j = 0; j < mm - 1; j++)
		{
			// colocamos los vertices en sentido antihorario para que las normales esten bien
			// 
			//	d -- c
			//	|    |
			//  a -- b

			int indice = i * mm + j;

			// poner "% (nn * mm)" sirve para prevenir que el indice salga del array

			//------------- TRIANGULO 1 ---------------

			m->vIndexes[indiceMayor] = indice; // a
			indiceMayor++;

			m->vIndexes[indiceMayor] = (indice + mm) % (nn * mm); // b
			indiceMayor++;

			m->vIndexes[indiceMayor] = (indice + mm + 1) % (nn * mm); // c
			indiceMayor++;

			//------------- TRIANGULO 2 ---------------

			m->vIndexes[indiceMayor] = (indice + mm + 1) % (nn * mm); // c
			indiceMayor++;

			m->vIndexes[indiceMayor] = (indice + 1);// % (nn * mm); // d
			indiceMayor++;

			m->vIndexes[indiceMayor] = indice;// % (nn * mm); // a
			indiceMayor++;
		}
	}

	// construimos las normales
	m->vNormals.reserve(m->mNumVertices);
	m->buildNormalVectors();

	return m;
}

#pragma endregion

#pragma region Practicas Examen

IndexMesh* IndexMesh::generateIndexedOctaedro(GLdouble l)
{
	IndexMesh* mesh = new IndexMesh();

	mesh->mNumVertices = 6;

	//			   0
	//			 / || \
	//			3--24--1
	//           \ || /
	//			   5

	GLdouble s = l / 2;
	// Aniade los 8 vertices del cubo a la mesh
	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vVertices.emplace_back(0, s, 0);		// v0
	mesh->vVertices.emplace_back(s, 0, 0);		// v1
	mesh->vVertices.emplace_back(0, 0, s);		// v2
	mesh->vVertices.emplace_back(-s, 0, 0);		// v3
	mesh->vVertices.emplace_back(0, 0, -s);		// v4
	mesh->vVertices.emplace_back(0, -s, 0);		// v5



	// Indices para la creacion de primitivas
	mesh->mNumIndexes = 24;
	mesh->vIndexes = new GLuint[mesh->mNumIndexes];

	GLuint arr[24] = {
		// Caras arriba
		0,2,1,
		0,1,4,
		0,4,3,
		0,3,2,
		// Caras abajo
		5,1,2,
		5,2,3,
		5,3,4,
		5,4,1
	};

	for (int i = 0; i < mesh->mNumIndexes; i++) {

		mesh->vIndexes[i] = arr[i];
	}

	mesh->vCaras.resize(mesh->mNumIndexes / VERTEX_CARA);
	for (int i = 0; i < mesh->mNumVertices / VERTEX_CARA; i++)
	{
		mesh->vCaras[i].vec1 = mesh->vVertices[mesh->vIndexes[i * VERTEX_CARA]];
		mesh->vCaras[i].id1 = mesh->vIndexes[i * VERTEX_CARA];

		mesh->vCaras[i].vec2 = mesh->vVertices[mesh->vIndexes[(i * VERTEX_CARA) + 1]];
		mesh->vCaras[i].id2 = mesh->vIndexes[(i * VERTEX_CARA) + 1];

		mesh->vCaras[i].vec3 = mesh->vVertices[mesh->vIndexes[(i * VERTEX_CARA) + 2]];
		mesh->vCaras[i].id3 = mesh->vIndexes[(i * VERTEX_CARA) + 2];
	}

	mesh->buildNormalVectors();

	return mesh;
	return nullptr;
}

Mesh* Mesh::generaPiramide(GLdouble l)
{
	Mesh* mesh = new Mesh();

	// CREAMOS LOS VERTICES USANDO EL TRIANGLE FAN PARA QUE TODOS LOS VERTICES SE JUNTEN CON EL PRIMERO
	mesh->mPrimitive = GL_TRIANGLE_FAN;

	//			 0
	//		   /||\
	//		  / || \
	//       1--24--3
	//

	//mitad del lado de la piramide
	GLdouble r = l / 2;

	// reservamos los vertices
	mesh->mNumVertices = 6;
	mesh->vVertices.reserve(mesh->mNumVertices);

	// Vertice superior de la piramide
	mesh->vVertices.emplace_back(0, l, 0); // V0

	mesh->vVertices.emplace_back(-r, 0, -r);	// V1
	mesh->vVertices.emplace_back(-r, 0, r);		// V2
	mesh->vVertices.emplace_back(r, 0, r);		// V3
	mesh->vVertices.emplace_back(r, 0, -r);		// V4


	mesh->vVertices.push_back(mesh->vVertices[1]); // V1.

	// GENERAMOS LAS COORDENADAS DE LAS TEXTURAS
	mesh->vTexCoords.reserve(mesh->mNumVertices);

	mesh->vTexCoords.emplace_back(0.5, 0.5);

	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(0, 0.5);
	mesh->vTexCoords.emplace_back(0, 0);
	mesh->vTexCoords.emplace_back(0.5, 0);


	mesh->vTexCoords.emplace_back(0, 0);

	return mesh;
}

#pragma endregion

