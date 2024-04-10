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
	void sceneDirLight(Camera const& cam) const {
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

	int mId;

	std::vector<Abs_Entity*> gObjects; // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures; // Entidades
};

#endif //_H_Scene_H_
