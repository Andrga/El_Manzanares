// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "ecs.h"

namespace ecs {

/*
 * Classes that inherit from Component must define a field
 *
 *   	constexpr static ecs::cmpId_type id = value;
 *
 * where value is from the enum ecs::cmpId (see ecs.h). This
 * how we assign numeric identifiers to components (so we can
 * easily put them in an array). The list of possible identifiers
 * is defined as an enum in ecs.h
 *
 */
class Component {
public:
	Component() :
			ent_(), //
			mngr_() //
	{
	}

	// Destroys the component.
	// Careful! ent_ and mngr_ should not be destroyed
	//
	virtual ~Component() {
	}

	// This method is used to set the context, which is a
	// reference to the entity in which the component is
	// installed and a reference to the manager. It will
	// be called by Entity when adding a component.
	//
	inline void setContext(entity_t ent, Manager *mngr) {
		ent_ = ent;
		mngr_ = mngr;
	}

	// We assume that initComponent will be called when adding a
	// component to an entity, immediately after setContext.
	//
	virtual void initComponent() {
	}

	// A component has an update method, and by default it
	// does nothing -- some components will not override this
	// method.
	//
	virtual void update() {
	}

	// A component has a render method, and by default it
	// does nothing -- some components will not override this
	// method.
	//
	virtual void render() {
	}

protected: // we allow direct use these fields from subclasses

	entity_t ent_; // a pointer to the entity, should not be deleted on destruction
	Manager *mngr_; //  a pointer to the manager, should not be deleted on destruction
};

} // end of namespace
