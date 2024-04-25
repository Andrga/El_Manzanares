#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include <vector>

class Mesh
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	Mesh() = default;
	virtual ~Mesh() = default;

	Mesh(const Mesh& m) = delete;            // no copy constructor
	Mesh& operator=(const Mesh& m) = delete; // no copy assignment

#pragma region P1

	static Mesh* generateRegularPolygon(GLuint num, GLdouble r); //Ejercicio2.
	static Mesh* generateRGBTriangle(GLdouble r); // Ejercicio6.
	/// <param name="w">With</param>
	/// <param name="h">Height</param>
	/// <param name="d">Depth</param>
	static Mesh* generateRectangle(GLdouble w, GLdouble h, GLdouble d); // Ejercicio8.
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h, GLdouble z); // Ejercicio8.
	static Mesh* generateCube(GLdouble l); // Ejercicio9.
	static Mesh* generateRGBCubeTriangles(GLdouble length); // Ejercicio10.

#pragma endregion
#pragma region P2

	/// <param name="w">With</param>
	/// <param name="h">Height</param>
	/// <param name="d">Depth</param>
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h); // Ejercicio19.
	static Mesh* generateRectangleTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh); // Ejercicio20.
	static Mesh* generateBoxOutline(GLdouble length);// Ejercicio21.
	static Mesh* generateBoxOutlineTexCor(GLdouble longitud); // Ejercicio23.
	static Mesh* generateStar3D(GLdouble re, GLuint np, GLdouble h); // Ejercicio25.
	static Mesh* generateStar3DTexCor(GLdouble re, GLuint np, GLdouble h); // Ejercicio28.
#pragma endregion
#pragma region P4
	//------Ejercicio60: 
	// h1: altura del centro a la parte mas alta, 
	// h2: altura desde el centro hasta cuando se dobla el ala, 
	// d: largo del ala.
	static Mesh* generateTIEWing(GLdouble h1, GLdouble h2, GLdouble d);
#pragma endregion

	virtual void render() const;

	GLuint size() const { return mNumVertices; }; // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };

protected:
	GLuint mPrimitive =
		GL_TRIANGLES;          // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0; // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices; // vertex array
	std::vector<glm::dvec4> vColors;   // color array
	virtual void draw() const;

	std::vector<glm::dvec2> vTexCoords;

	//----Ejercicio61:
	std::vector<glm::dvec3> vNormals;
};

class IndexMesh : public Mesh {
public:
	IndexMesh();
	~IndexMesh();
	void render() const override;
	void draw() const override;

	//------Ejercicio63:
	static IndexMesh* generateIndexedBox(GLdouble l);
	
	//------Ejercicio65:
	void buildNormalVectors();


protected:
	GLuint* vIndexes = nullptr;
	int mNumIndexes = 0;

};

#endif //_H_Scene_H_
