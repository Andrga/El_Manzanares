#include "MiraculousComponent.h"

#include "../sdlutils/SDLUtils.h"

MiraculousComponent::MiraculousComponent(uint32_t n) :nTime(n*1000)

{}

MiraculousComponent::~MiraculousComponent() {

}

void MiraculousComponent::initComponent()
{
	timeToConvert = sdlutils().virtualTimer().currTime(); // Tiempo para que se convierta en milagrosa.
	resetMiraculous();
}

void MiraculousComponent::update() {

	//if (!isMiracle && (sdlutils().virtualTimer().currTime() - timeToConvert) >= nTime) // Caundo pasa el NTime se tiene que convertir a fruta milagrosa.
	//{
	//	std::cout << "Se convierte en milagrosa." << std::endl;
	//	isMiracle = true;
	//	mTime = sdlutils().rand().nextInt(1, 6) * 1000; // Generamos un tiempo aleatorio para que deje de ser milagrosa.
	//	timeToDesConvert = sdlutils().virtualTimer().currTime();
	//}

	//if (isMiracle && (sdlutils().virtualTimer().currTime() - timeToDesConvert) >= mTime)
	//{
	//	std::cout << "Se deja de ser milagrosa." << std::endl;
	//	isMiracle = false;
	//}
}

void MiraculousComponent::resetMiraculous()
{
	std::cout << "Se deja de ser milagrosa." << std::endl;
	timeToConvert = sdlutils().virtualTimer().currTime();
	isMiracle = false;
}

void MiraculousComponent::setMiraculous()
{
	std::cout << "Se convierte en milagrosa." << std::endl;
	isMiracle = true;
	mTime = sdlutils().rand().nextInt(1, 5) * 1000; // Generamos un tiempo aleatorio para que deje de ser milagrosa.
	timeToDesConvert = sdlutils().virtualTimer().currTime();
}
