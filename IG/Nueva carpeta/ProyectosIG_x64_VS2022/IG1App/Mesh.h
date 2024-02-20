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

	static Mesh* generateRegularPolygon(GLuint num, GLdouble r); //Ejercicio2.
	static Mesh* generateRGBTriangle(GLdouble r); // Ejercicio6.
	static Mesh* generateRectangle(GLdouble w, GLdouble h); // Ejercicio8.
	static Mesh* generateRGBRectangle(GLdouble w, GLdouble h); // Ejercicio8.
	static Mesh* generateCube(GLdouble l); // Ejercicio9.
	static Mesh* generateRGBCubeTriangles(GLdouble length); // Ejercicio10.

	
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
};

#endif //_H_Scene_H_
