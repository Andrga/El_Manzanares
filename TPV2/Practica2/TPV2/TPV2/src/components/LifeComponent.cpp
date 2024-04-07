#include "LifeComponent.h"
#include "../ecs/Manager.h"
#include "InmuneComponent.h"


LifeComponent::LifeComponent(int maxLifes, const std::string texture)
	: maxLifes_(maxLifes), lifeText_(&sdlutils().images().at(texture))
{
	resetLifes();
}

void LifeComponent::hit()
{
	auto pc = mngr_->getHandler(ecs::hdlr::PACMAN);
	auto pcInm = mngr_->getComponent<InmuneComponent>(pc);
	if (!pcInm->getImmunity()) {
		if (lifes_ <= 0)
		{
			// Mensaje se acaba el juego
			Message m;
			m.id = _m_GAME_OVER;
			mngr_->send(m);
			//sdlutils().soundEffects().at("pacman_eat").play(0, 1);
		}
		else
		{
			lifes_--;

			// Mensaje reinicia la ronda
			Message m;
			m.id = _m_ROUND_OVER;
			mngr_->send(m);
			//sdlutils().soundEffects().at("pacman_eat").play(0, 1);
		}
	}
}

void LifeComponent::render()
{
	Vector2D pos(10, 5);
	SDL_Rect rendRect = build_sdlrect(pos, 30, 30);

	// Render icono de la vida
	for (int i = 0; i < lifes_; i++)
	{
		lifeText_->render(rendRect);
		rendRect.x += 40;
	}
}
