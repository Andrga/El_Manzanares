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
	for (int i = 0; i <= NSCENES; i++)
	{
		gObjects.push_back(std::vector<Abs_Entity*>());
		gObjects[i].push_back(new EjesRGB(400.0));
	}
	//------Ejercicio5:
		//gObjects.push_back(new RegularPolygon(3, 200.0)); // Triangulo cian.
		//gObjects[gObjects.size() - 1]->setColor(dvec4(0, 1, 1, 1));
		//gObjects.push_back(new RegularPolygon(100, 200.0)); // Circulo morado.
		//gObjects[gObjects.size() - 1]->setColor(dvec4(1, 0, 0.8, 1));
	//------Ejercicio6:
	/*gObjects.push_back(new RGBTriangle(200.0)); // Triangulo RGB.
	gObjects[gObjects.size() - 1]->setColor(dvec4(0, 1, 1, 1));*/
	//------Ejercicio8:
	// gObjects.push_back(new RGBRectangle(100.0, 200.0));
	//------Ejercicio9:
	//gObjects.push_back(new Cube(100.0));
	//------Ejercicio10:
	//gObjects.push_back(new RGBCube(100.0));


}

void Scene::addEntity(Abs_Entity* ent, uint16_t scene) {
	gObjects[scene].push_back(ent);
}

void
Scene::free()
{ // release memory and resources

	for (auto s : gObjects) {
		for (auto el : s) {
			delete el;
			el = nullptr;
		}
	}
}
void
Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);          // enable Depth test
	glEnable(GL_TEXTURE_2D);
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_BLEND);	// Para el Blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Para el alpha.
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_BLEND);
}

void
Scene::render(Camera const& cam) const
{
	sceneDirLight(cam); // Ejercicio56.

	cam.upload();

	for (Abs_Entity* el : gObjects[mId]) {
		el->render(cam.viewMat());
	}
}


//------Ejercicio13:
void Scene::update() {

	//------Ejercicio16:
	glutPostRedisplay();
	for (Abs_Entity* el : gObjects[mId]) {
		el->update();
	}
}

//------Ejercicio56:
void Scene::sceneDirLight(Camera const& cam) const {/*
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));*/
}