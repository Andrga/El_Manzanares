// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>
#include <bitset>
#include <cassert>
#include <vector>

#include "Component.h"
#include "ecs.h"

namespace ecs {

/*
 * A struct that represents a collection of components.
 *
 */
struct Entity {
public:
	Entity(grpId_t gId) :
			currCmps_(),
			cmps_(), //
			alive_(),  //
			gId_(gId) //
	{
		// We reserve the a space for the maximum number of
		// components. This way we avoid resizing the vector.
		//
		currCmps_.reserve(ecs::maxComponentId);
	}

	// we delete the copy constructor/assignment because it is
	// not clear how to copy the components
	//
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	// Exercise: define move constructor/assignment for class Entity

	// Destroys the entity
	//
	virtual ~Entity() {

		// we delete all available components
		//
		for (auto c : cmps_)
			if (c != nullptr)
				delete c;
	}


private:

	// the field currCmps_ can be removed, and instead we can traverse cmps_
	// and process non-null elements. We keep it because sometimes the order
	// in which the components are executed is important

	friend Manager;

	// the list of components is not really needed when using systems,
	// but for now we keep it just in case
	//
	std::vector<Component*> currCmps_;
	std::array<Component*, maxComponentId> cmps_;
	bool alive_;
	ecs::grpId_t gId_;
};

} // end of name space
