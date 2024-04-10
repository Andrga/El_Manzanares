#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

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

	void addEntity(Abs_Entity* ent);

	void init();

	void render(Camera const& cam) const;

	void update();

	void setScene(int id) { mId = id; }

protected:
	void free();
	void setGL();
	void resetGL();

	//------Ejercicio56:
	void sceneDirLight(Camera const& cam) const;

	int mId;

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; // Entidades
};

#endif //_H_Scene_H_
