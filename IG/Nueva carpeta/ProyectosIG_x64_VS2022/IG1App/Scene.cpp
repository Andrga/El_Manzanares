#include "Scene.h"
#include "CheckML.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Light.h"

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings
	setLights(); // Settea las luces de la escena. Ejercicio75.

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene


	//------Ejes:
	for (int i = 0; i <= NSCENES; i++)
	{
		gObjects.push_back(std::vector<Abs_Entity*>());
		gObjects[i].push_back(new EjesRGB(400.0));

		RGBTriangle* triangle = new RGBTriangle(50.0, 200.0, 0.0);

		switch (i)
		{
		case 0:
			addEntity(new RGBRectangle(300.0, 200.0, 0.0), 0);
			addEntity(new RegularPolygon(100, 200.0), 0);

			//triangle->setModelMat(glm::translate(nf1->modelMat(), glm::dvec3(200, 0, 0)));

			nf1 = new CompoundEntity();
			nf1->addEntity(triangle);
			nf2 = new CompoundEntity();

			nf2->addEntity(nf1);
			nf1->setModelMat(translate(nf2->modelMat(), glm::dvec3(200, 0, 0)));
			//addEntity(triangle, 0);
			addEntity(nf2, 0);
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
			head = new Sphere(30, 1, 0.5, 0);
			addEntity(head, 3);
			// Barba:
			beard = new PartialDisk(10, 30, 90, 180, 0, 1, 0);
			beard->setModelMat(translate(beard->modelMat(), dvec3(0, 0, 20)));
			addEntity(beard, 3);
			// Sombrero:
			cap = new Disk(0, 40, 1, 0, 0);
			cap->setModelMat(rotate(dmat4(1.0), radians(90.0), dvec3(1.0, 0.0, 0.0)) * translate(cap->modelMat(), dvec3(0, 0, -25))); //PAIGRO AQUI.	
			addEntity(cap, 3);
			// Ojo1:
			eye1 = new Cylinder(5, 1, 15, 0, 0, 0.5);
			eye1->setModelMat(translate(eye1->modelMat(), dvec3(10, 0, 25)));
			addEntity(eye1, 3);
			// Ojo2:
			eye2 = new Cylinder(5, 1, 15, 0.29, 0.34, 0.4);
			eye2->setModelMat(translate(eye2->modelMat(), dvec3(-10, 0, 25)));
			addEntity(eye2, 3);

			tie2 = new AdvancedTIEX_1();
			tie2->setModelMat(translate(tie2->modelMat(), dvec3(0, 0, 200))); // Quito esto para que al meterlo en el noto rotate no se desplace mas de la cuenta.
			addEntity(tie2, 3);
			break;
		case 4:
			//------Ejercicio60: TIE.
			// Caza:
			tie = new AdvancedTIEX_1();
			//tie->setModelMat(translate(tie->modelMat(), dvec3(0, 150, 0))); // Quito esto para que al meterlo en el noto rotate no se desplace mas de la cuenta.
			//addEntity(tie, 4); // Tecnicamente si estan en los nodos no hace falta meterlos en la escena se meteran con el nodo i guess.

			// Tatooine:
			tatooine = new Sphere(800, 1, 0.91, 0);
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
			//------Ejercicio71:
			addEntity(new RevSphere(500.0, 4.0, 6.0), 6);
			//addEntity(new RGBCube(49), 6);
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
//----Ejercicio75:
void Scene::setLights()
{
	//----Ejercicio76:
	dirLight = new DirLight();
	// Settea la dirLight.
	fvec4 v = { 1, 1, 1, 0 };
	fvec4 ambient = { 0, 0, 0, 1 };
	fvec4 diffuse = { 1, 1, 1, 1 };
	fvec4 specular = { 0.5, 0.5, 0.5, 1 };

	dirLight->setPosDir(v);
	dirLight->setAmbient(ambient);
	dirLight->setDiffuse(diffuse);
	dirLight->setSpecular(specular);
	dirLight->setID(GL_LIGHT0); // Le pone el id.

	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(v)); // Posicion de la luz.

	lights.push_back(dirLight);

	//----Ejercicio77:
	posLight = new PosLight();
	// Settea la dirLight.
	v = { 1, 1, 1, 0 };
	ambient = { 0, 0, 0, 1 };
	diffuse = { 1, 1, 1, 1 };
	specular = { 0.5, 0.5, 0.5, 1 };

	posLight->setPosDir(v);
	posLight->setAmbient(ambient);
	posLight->setDiffuse(diffuse);
	posLight->setSpecular(specular);
	posLight->setID(GL_LIGHT0); // Le pone el id.

	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(v)); // Posicion de la luz.

	lights.push_back(posLight);



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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Para el alpha.ç
	glEnable(GL_LIGHTING); // Activar la luz.
	glEnable(GL_NORMALIZE);
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING); // Desactivar la luz.
	glDisable(GL_NORMALIZE);
}

void
Scene::render(Camera const& cam) const
{
	//sceneDirLight(cam); // Ejercicio56. Comentado por ejercicio76.

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

	if (mId == 0 && nf1 != nullptr && nf2 != nullptr)
	{
		nf2->setModelMat(glm::rotate(nf2->modelMat(),
			radians(3.0), dvec3(0, 0, 1)));

		nf1->setModelMat(glm::rotate(nf2->modelMat(),
			radians(-3.0), dvec3(0, 0, 1)));
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

//----Ejercicio76:
void Scene::activateDirLight()
{
	dirLight->enable();
}
void Scene::deactivateDirLight()
{
	dirLight->disable();
}
//----Ejercicio77:
void Scene::activatePosLight()
{
	posLight->enable();
}
void Scene::deactivatePosLight()
{
	posLight->disable();
}
//----Ejercicio78:
void Scene::activateSpotLight()
{
	spotLight->enable();
}
void Scene::deactivateSpotLight()
{
	spotLight->disable();
}
//----Ejercicio79:
void Scene::activateTieSpotLight()
{
	tieSpotLight->enable();
}
void Scene::deactivateTieSpotLight()
{
	tieSpotLight->disable();
}