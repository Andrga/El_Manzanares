#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene

	//------Ejes:
	gObjects.push_back(new EjesRGB(400.0));
	//------Ejercicio5:
		//gObjects.push_back(new RegularPolygon(3, 200.0)); // Triangulo cian.
		//gObjects[gObjects.size() - 1]->setColor(dvec4(0, 1, 1, 1));
		//gObjects.push_back(new RegularPolygon(100, 200.0)); // Circulo morado.
		//gObjects[gObjects.size() - 1]->setColor(dvec4(1, 0, 0.8, 1));
	//------Ejercicio6:
	/*gObjects.push_back(new RGBTriangle(200.0)); // Triangulo RGB.
	gObjects[gObjects.size() - 1]->setColor(dvec4(0, 1, 1, 1));*/
	//------Ejercicio8:
	//gObjects.push_back(new RGBRectangle(100.0, 200.0));
	//------Ejercicio9:
	//gObjects.push_back(new Cube(100.0));
	//------Ejercicio10:
	//gObjects.push_back(new RGBCube(100.0));


}

void Scene::addEntity(Abs_Entity* ent) {

	gObjects.push_back(ent);
}

void
Scene::free()
{ // release memory and resources

	for (Abs_Entity* el : gObjects) {
		delete el;
		el = nullptr;
	}
}
void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
}

void
Scene::render(Camera const& cam) const
{
	cam.upload();

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());
	}
}
