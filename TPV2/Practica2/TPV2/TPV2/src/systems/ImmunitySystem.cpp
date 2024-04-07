#include "ImmunitySystem.h"

#include "../components/InmuneComponent.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

ImmunitySystem::ImmunitySystem() {

}

void ImmunitySystem::initSystem()
{
	// Coge la primera entidad del grupo de entidades PACMAN para podes acceder a su componente Inmune.
	auto pacManEnt = mngr_->getEntities(ecs::hdlr::PACMAN);
	pacMan = *pacManEnt.begin();
}

void ImmunitySystem::update()
{
	isImmune = mngr_->getComponent<InmuneComponent>(pacMan)->getImmunity();
	//std::cout << "Inmunidad: " << isImmune << std::endl;
	if (isImmune && (sdlutils().virtualTimer().currTime() - time) >= TIME_INMUNE)
	{
		//std::cout << "Inmunidad acabada." << std::endl;
		// Enviar el mensaje de que se ha acabdo la inmunidad.
		Message message;
		message.id = _m_IMMUNITY_END;
		mngr_->send(message, true);
	}
}

void ImmunitySystem::recieve(const Message& men)
{
	switch (men.id)
	{
	case  _m_IMMUNITY_START:
		if (!isImmune)
		{
			isImmune = true;
			mngr_->getComponent<InmuneComponent>(pacMan)->setInmune(isImmune);
			time = sdlutils().virtualTimer().currTime(); // Tiempo en el que empieza la inmunidad.	
		}
		break;
	default:
		break;
	}
}