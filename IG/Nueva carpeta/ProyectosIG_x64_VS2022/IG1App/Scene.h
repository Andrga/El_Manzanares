#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

const int NSCENES = 5;

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

	void rotate(); // Ejercicio68.
	void orbit(); // Ejercicio68.

protected:
	void free();
	void setGL();
	void resetGL();

	//------Ejercicio56:
	void sceneDirLight(Camera const& cam) const;

	int mId;

	// Cosas de la cabeza: ejercicio58.
	Abs_Entity* head; // Cabeza del granjero del ejercicio58.
	Abs_Entity* beard; // Barba del granjero del ejercicio58.
	Abs_Entity* eye1; // Ojo1 del granjero del ejercicio58.
	Abs_Entity* eye2; // Ojo2 del granjero del ejercicio58.
	Abs_Entity* cap; // Sombrero del granjero del ejercicio58.



	// Cosas del TIE: ejercicio60.
	Abs_Entity* tie; // Tie del ejercicio60.
	CompoundEntity* inventedNodeOrbit; // Nodo del orbit del ejercicio68.
	CompoundEntity* inventedNodeRotate; // Nodo del rotate del ejercicio68.
	Abs_Entity* tatooine; // Planeta del ejercicio67.

	std::vector<std::vector<Abs_Entity*> > gObjects; // Entities (graphic objects) of the scene actual
	std::vector<Texture*> gTextures; // Entidades
};

#endif //_H_Scene_H_
