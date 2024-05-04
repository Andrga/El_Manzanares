// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>

#include "../sdlutils/SDLNetUtils.h"
class UDPServer {
public:
	UDPServer(const Uint16 port, uint8_t max_clients);
	virtual ~UDPServer();
	void listen();

private:

	template<typename T>
	void send_to_all_excpet(T &m, int ex_id = -1) {
		Uint8 *end = m.serialize(p_->data);
		p_->len = end - p_->data;
		send_packet_to_all_excpet(ex_id);
	}

	void send_packet_to_all_excpet(int ex_id = -1) {
		for (auto i = 0u; i < max_clients_; i++) {
			if (i != static_cast<Uint8>(ex_id) && clients_[i].connected) {
				p_->address = clients_[i].address;
				SDLNet_UDP_Send(sock_, -1, p_); // we just forward the whole packet, it is supposed to be ready
			}
		}
	}

	int who_is_the_master() {
		for (auto i = 0u; i < max_clients_; i++) {
			if (clients_[i].connected)
				return i;
		}

		return -1;
	}


	struct ClientInfo {
		bool connected;
		IPaddress address;
	};

	UDPsocket sock_;
	UDPpacket *p_;
	SDLNet_SocketSet socketSet_;
	uint8_t max_clients_;
	ClientInfo *clients_;
	Uint16 port_;
	bool done_;
};

