#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Light.h"

#include <vector>

const int NSCENES = 7;

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

	void switchDirlight(bool s) {
		s ? dirLight->enable() : dirLight->disable();
	}
	void switchPoslight(bool s) {
		s ? posLight->enable() : posLight->disable();
	}
	void switchSpotlight(bool s) {
		s ? spotLight->enable() : spotLight->disable();
	}
	void switchTIESpotlight(bool s) {
		tie->switchFoco(s);
	}
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



	// Cosas del TIE: ejercicio60.
	AdvancedTIEX_1* tie; // Tie del ejercicio60.
	Abs_Entity* tie2; // Para la profesora.
	CompoundEntity* inventedNodeOrbit; // Nodo del orbit del ejercicio68.
	CompoundEntity* inventedNodeRotate; // Nodo del rotate del ejercicio68.
	Abs_Entity* tatooine; // Planeta del ejercicio67.

	std::vector<std::vector<Abs_Entity*> > gObjects; // Entities (graphic objects) of the scene actual
	std::vector<Texture*> gTextures; // Entidades

	//------Ejercicio66:
	CompoundEntity* nf1; // Nodo del orbit del ejercicio68.
	CompoundEntity* nf2; // Nodo del orbit del ejercicio68.

	//------Ejercicio76:
	DirLight* dirLight;
	PosLight* posLight;
	SpotLight* spotLight;
	void setLights();

	

};

#endif //_H_Scene_H_
