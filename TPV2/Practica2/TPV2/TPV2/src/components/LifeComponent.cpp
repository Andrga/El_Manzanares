#include "LifeComponent.h"



LifeComponent::LifeComponent(int maxLifes, const std::string texture)
	: maxLifes_(maxLifes), lifeText_(&sdlutils().images().at(texture))
{
	resetLifes();
}

void LifeComponent::render()
{
	Vector2D pos(10, 5);
	SDL_Rect rendRect = build_sdlrect(pos, 30, 30);

	for (int i = 0; i < lifes_; i++)
	{
		lifeText_->render(rendRect);
		rendRect.x += 40;
	}
}
