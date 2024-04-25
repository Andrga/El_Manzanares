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

		switch (i)
		{
		case 0:
			addEntity(new RGBRectangle(300.0, 200.0, 0.0), 0);
			addEntity(new RGBTriangle(50.0, 200.0, 0.0), 0);
			addEntity(new RegularPolygon(100, 200.0), 0);
			break;
		case 1:
			addEntity(new RGBCube(100.0), 1);
			break;
		case 2:
			addEntity(new Ground(200.0, 200.0, 4, 4, "../bmps/baldosaC.bmp"), 2);
			addEntity(new BoxOutline(200, "../bmps/container.bmp", "../bmps/papelE.bmp"), 2);
			addEntity(new Star3D(100, 8, 100, "../bmps/baldosaP.bmp"), 2); // Ejercicio28.
			addEntity(new GlassParapet(300, "../bmps/windowV.bmp"), 2); // Ejercicio31.
			addEntity(new Photo(500), 2); // Ejercicio31.
			break;
		case 3:
			// Cabeza:
			head = new Sphere(30, 255, 165, 0);
			addEntity(head, 3);
			// Barba:
			beard = new PartialDisk(4, 6, 80, 180, 0, 255, 0);
			beard->setModelMat(translate(beard->modelMat(), dvec3(100, 0, 0)));
			addEntity(beard, 3);
			// SObrero:
			cap = new Disk(0, 40, 255, 0, 0);
			//cap->setModelMat(rotate(dmat4(1.0), radians(90.0), dvec3(0.0, 1.0, 0.0))); //PAIGRO AQUI.	
			addEntity(cap, 3);


			break;
		case 4:
			//------Ejercicio60: TIE.
			// Caza:
			tie = new AdvancedTIEX_1();
			//tie->setModelMat(translate(tie->modelMat(), dvec3(0, 150, 0))); // Quito esto para que al meterlo en el noto rotate no se desplace mas de la cuenta.
			//addEntity(tie, 4); // Tecnicamente si estan en los nodos no hace falta meterlos en la escena se meteran con el nodo i guess.

			// Tatooine:
			tatooine = new Sphere(800, 255, 233, 0);
			//addEntity(tatooine, 4); // Lo mismo que con el TIE.

			// Nodo orbit:
			inventedNodeOrbit = new CompoundEntity();
			// Nodo rotate:
			inventedNodeRotate = new CompoundEntity();

			addEntity(inventedNodeOrbit, 4);


			inventedNodeRotate->setModelMat(translate(inventedNodeOrbit->modelMat(), dvec3(0, 500, 0))); // Movemps el nodo de rotacion para que rote a cierta distancia del planeta.

			inventedNodeRotate->addEntity(tie); // Le metemos al nodo rotate el tie para que se ponga en su posicion y rote ahi.

			inventedNodeOrbit->addEntity(inventedNodeRotate); // Le metemos el noto rotate al otro nodo.
			inventedNodeOrbit->addEntity(tatooine); // Le metemos Tatooine al nodo orbit.



			break;
		case 5:
			//------Ejercicio64:
			addEntity(new IndexedBox(100, 0.0, 1.0, 0.0), 5);
			break;
		case 6:
			tie2 = new AdvancedTIEX_1();
			addEntity(tie2, 6);
			break;
		default:
			break;
		}
	}

	/*//------Ejercicio5:
		//gObjects.push_back(new RegularPolygon(3, 200.0)); // Triangulo cian.
		//gObjects[gObjects.size() - 1]->setColor(dvec4(0, 1, 1, 1));
		//gObjects.push_back(new RegularPolygon(100, 200.0)); // Circulo morado.
		//gObjects[gObjects.size() - 1]->setColor(dvec4(1, 0, 0.8, 1));
	//------Ejercicio6:
	gObjects.push_back(new RGBTriangle(200.0)); // Triangulo RGB.
	gObjects[gObjects.size() - 1]->setColor(dvec4(0, 1, 1, 1));
	//------Ejercicio8:
	// gObjects.push_back(new RGBRectangle(100.0, 200.0));
	//------Ejercicio9:
	//gObjects.push_back(new Cube(100.0));
	//------Ejercicio10:
	//gObjects.push_back(new RGBCube(100.0));*/


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
	// Ejercicio68.
	if (orbitTieBool)
	{
		rotateTie();
	}
	if (rotateTieBool)
	{
		orbitTie();
	}
}
// Ejercicio68.
void Scene::setScene(int id)
{
	mId = id;
	if (mId == 4)
	{
		glClearColor(0.0, 0.0, 0.0, 1.0); // background color (alpha=1 -> opaque)
	}
	else
	{
		glClearColor(0.6, 0.7, 0.8, 1.0); // background color (alpha=1 -> opaque)
	}
}
// Ejercicio68.
void Scene::rotateTie()
{
	tie->setModelMat(
		translate(inventedNodeRotate->modelMat(), dvec3(0, 0, 0)) * tie->modelMat());

	dvec3 point = glm::normalize(dvec3(tie->modelMat() * dvec4(0.0, 1.0, 0.0, 0.0)));
	inventedNodeRotate->setModelMat(rotate(dmat4(1), radians(-1.0), point));
}

void Scene::orbitTie()
{
	if (mId == 4)
	{
		tie->setModelMat(translate(inventedNodeOrbit->modelMat(), dvec3(0, 0, 0)) * tie->modelMat());

		dvec3 tieDirection = normalize(dvec3(tie->modelMat() * dvec4(0.0, 0.0, 1.0, 0.0)));

		inventedNodeOrbit->setModelMat(rotate(dmat4(1), radians(-1.0), tieDirection));
	}
}

void Scene::pseudoSetOrbtit()
{
	orbitTieBool = !orbitTieBool;
}

void Scene::pseudoSetRotate()
{
	rotateTieBool = !rotateTieBool;
}

//------Ejercicio56:
void Scene::sceneDirLight(Camera const& cam) const {
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
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}