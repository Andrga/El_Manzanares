#include "Scene.h"
#include "CheckML.h"
#include "Material.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

void
Scene::init()
{
	setGL(); // OpenGL settings

	// allocate memory and load resources
	// Lights
	setLights();
	// Textures

	// Graphics objects (entities) of the scene


	for (int i = 0; i <= NSCENES; i++)
	{
		//------Ejes:
		gObjects.push_back(std::vector<Abs_Entity*>());
		gObjects[i].push_back(new EjesRGB(400.0));

		RGBTriangle* triangle = new RGBTriangle(50.0, 200.0, 0.0);

		auto sp1 = new SphereMbR(100, 50, 50);
		auto sp2 = new SphereMbR(100, 50, 50);
		auto msp = new Material();

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
			addEntity(new ToroidMbR(100, 500, 50, 10), 6);
			break;
		case 7:
			// Tatooion con color
			sp1->setColor(glm::dvec4(1, 1, 0, 1));
			sp1->setModelMat(translate(sp1->modelMat(), dvec3(0, 0, 200)));

			// tatooin con material
			msp->setGold();
			sp2->setMaterial(msp);
			sp2->setModelMat(translate(sp2->modelMat(), dvec3(200, 0, 0)));

			// aniade las esferas a la escena
			addEntity(sp1, 7);
			addEntity(sp2, 7);

			break;

#pragma region Practicas Examen
		case 8:
			// Rombo generado reutilizando la esfera / malla de rebolucion
			// addEntity(new SphereMbR(100, 3, 4), 8);

			// Octaedro generado por malla indexada
			addEntity(new OctaedroTriangulos(100, "../bmps/windowC.bmp"), 8);

			break;
#pragma endregion


		default:
			break;
		}
	}



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
	glEnable(GL_DEPTH_TEST); // Activa el buffer (Z-buffer) contiene la distancia respecto a la camara
	glEnable(GL_TEXTURE_2D); // Activa el uso de las texturas
	glEnable(GLUT_MULTISAMPLE);
	glEnable(GL_BLEND);	// Activa el Blending (suma de colores de objetos distintos).
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Activa el alpha (Activa el blendeo de colores con el componente alpha).
	glEnable(GL_COLOR_MATERIAL); // Activa los materiales.
	glEnable(GL_LIGHTING); // Activacion de las luces.
}
void
Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0); // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);     // disable Depth test
	glDisable(GL_TEXTURE_2D);
	glDisable(GLUT_MULTISAMPLE);
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING); // 
}

void
Scene::render(Camera const& cam) const
{
	//sceneDirLight(cam); // Ejercicio56.

	// Actualizacion de las luces segun la camara
	dirLight->upload(cam.viewMat());
	posLight->upload(cam.viewMat());
	spotLight->upload(cam.viewMat());

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
	// Movimiento y rotacion del TIE por update
	//// Ejercicio68.
	//if (orbitTieBool)
	//{
	//	rotateTie();
	//}
	//if (rotateTieBool)
	//{
	//	orbitTie();
	//}

	// Rotacion del triangulo y la circunferencia (rehacedura de la practica 1)
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

// --------------- ROTACION TIE Y TATOOIN -----------------
//
// Tie rota sobre si mismo
void Scene::rotateTie()
{
	// Si la escena es la 4 (Escena de Tatooin)
	if (mId == 4)
	{
		// Alinea el TIE con el planeta
		tie->setModelMat(
			translate(inventedNodeRotate->modelMat(), dvec3(0, 0, 0)) * tie->modelMat());

		// Rota el TIE
		dvec3 point = glm::normalize(dvec3(tie->modelMat() * dvec4(0.0, 1.0, 0.0, 0.0)));
		inventedNodeRotate->setModelMat(rotate(dmat4(1), radians(-1.0), point));
	}
}
// Tie orbita alrededor del planeta
void Scene::orbitTie()
{
	// Si la escena es la 4 (Escena de Tatooin)
	if (mId == 4)
	{
		// Alinea el TIE con el planeta
		tie->setModelMat(translate(inventedNodeOrbit->modelMat(), dvec3(0, 0, 0)) * tie->modelMat());

		// Rota el TIE
		dvec3 tieDirection = normalize(dvec3(tie->modelMat() * dvec4(0.0, 0.0, 1.0, 0.0)));
		inventedNodeOrbit->setModelMat(rotate(dmat4(1), radians(-1.0), tieDirection));
	}
}

#pragma region Switch rotacion y orbita del TIE
void Scene::pseudoSetOrbtit()
{
	orbitTieBool = !orbitTieBool;
}

void Scene::pseudoSetRotate()
{
	rotateTieBool = !rotateTieBool;
}

#pragma endregion

// --------------- LUCES -----------------
//
// Metodo que renderiza una unica luz con los parametros asignados
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

// Metodo que settea las luces de la escena y sus parametros:
void Scene::setLights()
{
	dirLight = new DirLight();

	dirLight->setID(GL_LIGHT0);
	dirLight->setPosDir(dvec4(1, 1, 1, 0));
	dirLight->setAmbient(dvec4(0, 0, 0, 1));
	dirLight->setDiffuse(dvec4(1, 1, 1, 1));
	dirLight->setSpecular(dvec4(0.5, 0.5, 0.5, 1));

	posLight = new PosLight();

	posLight->setID(GL_LIGHT1);
	posLight->setAmbient(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	posLight->setDiffuse(glm::fvec4(1.0, 1.0, 0.0, 1.0));
	posLight->setSpecular(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	posLight->setPosDir(glm::fvec3(100.0, 1500.0, 0.0));

	spotLight = new SpotLight();

	spotLight->setID(GL_LIGHT2);
	spotLight->setAmbient(glm::fvec4(0.0, 0.0, 0.0, 1.0));
	spotLight->setDiffuse(glm::fvec4(1.0, 1.0, 1.0, 1.0));
	spotLight->setSpecular(glm::fvec4(0.5, 0.5, 0.5, 1.0));
	spotLight->setPosDir(glm::fvec3(100.0, 300.0, 3000.0));

}
