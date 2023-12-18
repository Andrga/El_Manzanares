#include "SceneObject.h"
#include "PlayState.h"

SceneObject::SceneObject(PlayState* plST, Point2D<double> pos, int wid, int hei, const Texture* tex) // Constructora.
	:GameObject(plST), playST(plST), position(pos), width(wid), height(hei), texture(tex)
{
	rect.w = wid;
	rect.h = hei;
}

void SceneObject::update(){}

void SceneObject::render() const {}

void SceneObject::save(ostream& fil) const {}

bool SceneObject::hit(SDL_Rect _rect, char c) { return true; }