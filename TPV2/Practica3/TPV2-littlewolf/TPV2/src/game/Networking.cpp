// This file is part of the course TPV2@UCM - Samir Genaim

#include "Networking.h"

#include <iostream>

#include "Game.h"
#include "LittleWolf.h"
#include "netwrok_messages.h"
#include "../sdlutils/SDLNetUtils.h"
#include "../utils/Vector2D.h"

Networking::Networking() :
	sock_(), //
	socketSet_(), //
	p_(), //
	srvadd_(), //
	clientId_(), //
	masterId_() {
	std::cout << "New networking" << std::endl;
}

Networking::~Networking() {
}

bool Networking::init(const char* host, Uint16 port) {

	if (SDLNet_ResolveHost(&srvadd_, host, port) < 0) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	sock_ = SDLNet_UDP_Open(0);
	if (!sock_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	p_ = SDLNet_AllocPacket(512);
	if (!p_) {
		SDLNetUtils::print_SDLNet_error();
		return false;
	}

	socketSet_ = SDLNet_AllocSocketSet(1);
	SDLNet_UDP_AddSocket(socketSet_, sock_);

	Msg m0;
	MsgWithMasterId m1;

	// request to connect
	m0._type = _CONNECTION_REQUEST;
	SDLNetUtils::serializedSend(m0, p_, sock_, srvadd_);

	bool connected = false;
	// wait 3sec for the response, if we don't get we stop (since done will be 'true')
	if (SDLNet_CheckSockets(socketSet_, 3000) > 0) {
		if (SDLNet_SocketReady(sock_)) {
			if (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {
				switch (m0._type) {
				case _CONNECTION_ACCEPTED:
					m1.deserialize(p_->data);
					clientId_ = m1._client_id;
					masterId_ = m1._master_id;
					connected = true;
					break;
				case _CONNECTION_REJECTED:
					break;
				}
			}
		}
	}

	if (!connected) {
		std::cerr << "Failed to get a client id" << std::endl;
		return false;
	}

#ifdef _DEBUG
	std::cout << "Connected with id " << (int)clientId_ << std::endl;
#endif

	return true;
}

bool Networking::disconnect() {
	MsgWithId m;
	m._type = _DISCONNECTED;
	m._client_id = clientId_;
	return (SDLNetUtils::serializedSend(m, p_, sock_, srvadd_) > 0);

}

void Networking::update() {
	Msg m0;
	MsgWithMasterId m1;
	PlayerStateMsg m2;
	ShootMsg m3;
	MsgWithId m4;
	PlayerInfoMsg m5;

	while (SDLNetUtils::deserializedReceive(m0, p_, sock_) > 0) {

		switch (m0._type) {
		case _NEW_CLIENT_CONNECTED:
			// informas al master de nuevo jugador conectado
			m1.deserialize(p_->data); // al enviar un mensaje hay que deserializarlo para poder usarlo
			masterId_ = m1._master_id; // guardas el nuevo master si hay que cambiarlo
			handle_new_client(m1._client_id); // se administra nuevo jugador
			break;

		case _DISCONNECTED:
			// informas al master de jugador desconectado
			m1.deserialize(p_->data);
			masterId_ = m1._master_id; // guardas el nuevo master si hay que cambiarlo
			handle_disconnet(0); // se administra la desconexion
			break;

		case _PLAYER_STATE:
			// para informar al master del estado de los jugadores
			m2.deserialize(p_->data);
			handle_player_state(m2);
			break;

		case _PLAYER_INFO:
			// para informar al master de info de los jugadores
			m5.deserialize(p_->data);
			handle_player_info(m5);
			break;

		case _SHOOT:
			// para informar al master de disparos
			m3.deserialize(p_->data);
			handle_shoot(m3);
			break;

		case _DEAD:
			// para informar al master de muertes
			m4.deserialize(p_->data);
			handle_dead(m4);
			break;

		case _RESTART:
			// para resetear
			handle_restart();
			break;
		case _WAITING:
			handle_waiting();
			break;
		case _SYNCRO:
			m5.deserialize(p_->data);
			handle_syncro(m5);
			break;
		default:
			break;
		}
	}
}

#pragma region Sends:

void Networking::send_state(const Vector2D& pos, float w, float h, float rot)
{
	PlayerStateMsg m; // Mensaje.

	// Pone el tipo al mensaje,
	m._type = _PLAYER_STATE;

	// Pone info al mensaje.
	m._client_id = clientId_;
	m.x = pos.getX();
	m.y = pos.getY();
	m.w = w;
	m.h = h;
	m.rot = rot;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_shoot(Vector2D pos, Vector2D vel, int width, int height, float r) {
	// Mensaje.
	ShootMsg m;

	// Pone el tipo de mensaje.
	m._type = _SHOOT; // Tipo de mensaje.

	// Pone info al mensaje.
	m._client_id = clientId_; // Id del mensaje.
	m.posX = pos.getX();
	m.posY = pos.getY();
	m.velX = vel.getX();
	m.velY = vel.getY();
	m.width = width;
	m.height = height;
	m.rot = r;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_dead(Uint8 id)
{
	MsgWithId m; // Mensaje.

	// Pone el tipo al mensaje.
	m._type = _DEAD;

	// Pone info al mensaje.
	m._client_id = id;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_my_info(const Vector2D& pos, const Vector2D& vel, float speed, float acceleration, float theta, Uint8 state)
{
	PlayerInfoMsg m; // Mensaje

	// Pone el tipo al mensaje.
	m._type = _PLAYER_INFO;

	// Mete la info al mensaje.
	m._client_id = clientId_;
	m.posX = pos.getX();
	m.posY = pos.getY();
	m.speed = speed;
	m.acceleration = acceleration;
	m.theta = theta;
	m.state = state;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_restart()
{
	Msg m; // Mensaje.

	// Pone el tipo al mensaje.
	m._type = _RESTART;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::sendPlayerInfo(const Vector2D& pos, const Vector2D& vel, float speed, float acceleration, float theta, Uint8 state)
{
	PlayerInfoMsg m; // Mensaje.

	// Pone el tipo al mensaje.
	m._type = _PLAYER_INFO;

	// Mete la info del jugador al mensaje.
	m._client_id = clientId_;
	m.posX = pos.getX();
	m.posY = pos.getY();
	m.velX = vel.getX();
	m.velY = vel.getY();
	m.speed = speed;
	m.acceleration = acceleration;
	m.theta = theta;
	m.state = state;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_waiting()
{
	Msg m; // Mensaje.

	// Pone el tipo al mensaje.
	m._type = _WAITING;

	// Manda el mensaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}

void Networking::send_syncro(Uint8 playerID, const Vector2D& pos)
{
	PlayerInfoMsg m; // Mensaje de tipo PlayerInfo.

	// Pone el tipo al mensaje.
	m._type = _SYNCRO;

	// Pone parametros al mensaje.
	m._client_id = playerID;
	m.posX = pos.getX();
	m.posY = pos.getY();

	// Manda el mesaje.
	SDLNetUtils::serializedSend(m, p_, sock_, srvadd_);
}
#pragma endregion

#pragma region Handlers:

void Networking::handle_new_client(Uint8 id)
{
	if (id != clientId_) {
		Game::instance()->getLittleWolf()->sendPlayerInfo();
	}
}

void Networking::handle_disconnet(Uint8 id)
{
	Game::instance()->getLittleWolf()->disconnetPlayer(id);
}

void Networking::handle_player_state(const PlayerStateMsg& m)
{
	if (m._client_id != clientId_) {
		//Game::instance()->getLittleWolf().update_player_state(m._client_id, m.x, m.y, m.w, m.h, m.rot);
	}
}

void Networking::handle_shoot(const ShootMsg& m)
{
	if (is_master())
	{
		Game::instance()->getLittleWolf()->processShoot(m._client_id);
	}
}

void Networking::handle_dead(const MsgWithId& m)
{
	if (m._client_id != clientId_)
	{
		Game::instance()->getLittleWolf()->processDie(m._client_id);
	}
}

void Networking::handle_player_info(const PlayerInfoMsg& m) {
	if (m._client_id != clientId_)
	{
		Game::instance()->getLittleWolf()->updatePlayerInfo(m._client_id, m.posX, m.posY, m.velX, m.velY, m.speed, m.acceleration, m.theta, m.state);
	}
}

void Networking::handle_restart()
{
	Game::instance()->getLittleWolf()->bringAllToLife();
}

void Networking::handle_waiting()
{
	Game::instance()->getLittleWolf()->processWaiting();
}

void Networking::handle_syncro(const PlayerInfoMsg& m)
{
	Game::instance()->getLittleWolf()->processSyncro(m._client_id, Vector2D(m.posX, m.posY));
}
#pragma endregion