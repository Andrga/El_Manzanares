#include "LifeComponent.h"

LifeComponent::LifeComponent(int maxLifes, const std::string texture) :
	maxLifes_(maxLifes), lifeText_(&sdlutils().images().at(texture)) {
	resetlifes();
}

void LifeComponent::render()
{
	SDL_Rect rendRect = build_sdlrect(0, 5, 30, 30);
	for (int i = 0; i < lifes_; i++)
	{
		lifeText_->render(rendRect);
		rendRect.x = (rendRect.x + 50);
	}
}
