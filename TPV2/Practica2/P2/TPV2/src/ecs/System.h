// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "ecs.h"
#include "messages.h"

namespace ecs {

/*
 * A class that represents a system. It only has an update method that will
 * be called from the main loop to do it tasks. You can add more methods that
 * represent more tasks. That depends much on the game you are developing.
 */
class System {
public:
	System() :
			mngr_(nullptr) {
	}

	//IMPORTANT: do not delete the reference to the manager on destruction
	virtual ~System() {
	}

	// will be called to set the context, in this case it is only a reference
	// to the manager
	//
	void setContext(Manager *mngr) {
		mngr_ = mngr;
	}

	// will be called after crating the system to initialise whatever should
	// be initialised
	//
	virtual void initSystem() {
	}

	// will be called so the system does it tasks, For some system it won't be
	// even called because they are there just to receive and react to messages
	//
	virtual void update() {
	}

	// a method to receive a message, will be called by the sender or
	// from the manager when a message is sent to all
	//
	// the struct msg is forward declared in ecs.h, the actual message will
	// be defined by the user
	//
	virtual void recieve(const Message&) {
	}

protected:
	Manager *mngr_;
};

} // end of namespace

