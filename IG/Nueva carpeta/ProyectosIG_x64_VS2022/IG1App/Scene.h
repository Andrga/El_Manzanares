#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

const int NSCENES = 6;
class Light;
class DirLight;
class PosLight;
class SpotLight;

class Scene
{
public:
	Scene() = default;
	~Scene()
	{
		free();
		resetGL();
	};

	Scene(const Scene& s) = delete;            // no copy constructor
	Scene& operator=(const Scene& s) = delete; // no copy assignment

	void addEntity(Abs_Entity* ent, uint16_t scene);

	void init();

	void render(Camera const& cam) const;

	void update();

	void setScene(int id);

	void rotateTie(); // Ejercicio68.
	void orbitTie(); // Ejercicio68.
	void pseudoSetOrbtit();
	void pseudoSetRotate();

	//----Ejercicio76:
	void activateDirLight();
	void deactivateDirLight();
	//----Ejrecicio77:
	void activatePosLight();
	void deactivatePosLight();
	//----Ejercicio78:
	void activateSpotLight();
	void deactivateSpotLight();
	//----Ejercicio79:
	void activateTieSpotLight();
	void deactivateTieSpotLight();

	void setLights(); // Ejercicio75.

protected:
	void free();
	void setGL();
	void resetGL();

	//------Ejercicio56:
	void sceneDirLight(Camera const& cam) const;

	int mId;

	bool rotateTieBool = false; // Booleano para controlar la rotacion sobre si mismo del Tie. 68.
	bool orbitTieBool = false; // Booleano para controlar la orbita del Tie al rededor de Tatooine. 68.

	// Cosas de la cabeza: ejercicio58.
	Abs_Entity* head; // Cabeza del granjero del ejercicio58.
	Abs_Entity* beard; // Barba del granjero del ejercicio58.
	Abs_Entity* eye1; // Ojo1 del granjero del ejercicio58.
	Abs_Entity* eye2; // Ojo2 del granjero del ejercicio58.
	Abs_Entity* cap; // Sombrero del granjero del ejercicio58.

	std::vector<Light*> lights;	// Ejercicio75.

	// Cosas del TIE: ejercicio60.
	Abs_Entity* tie; // Tie del ejercicio60.
	Abs_Entity* tie2; // Para la profesora.
	CompoundEntity* inventedNodeOrbit; // Nodo del orbit del ejercicio68.
	CompoundEntity* inventedNodeRotate; // Nodo del rotate del ejercicio68.
	Abs_Entity* tatooine; // Planeta del ejercicio67.

	std::vector<std::vector<Abs_Entity*> > gObjects; // Entities (graphic objects) of the scene actual
	std::vector<Texture*> gTextures; // Entidades

	//------Ejercicio66:
	CompoundEntity* nf1; // Nodo del orbit del ejercicio68.
	CompoundEntity* nf2; // Nodo del orbit del ejercicio68.

	DirLight* dirLight; // Ejercicio76.
	PosLight* posLight; // Ejercicio77.
	SpotLight* spotLight; // Ejercicio78.
	SpotLight* tieSpotLight; // Ejercicio79.
};

#endif //_H_Scene_H_
