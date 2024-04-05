// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "ecs.h"

namespace ecs {

/*
 * Structs that inherit from Component must define a field
 *
 *   	constexpr static ecs::cmpId_t id = value;
 *
 * where value is from the enum ecs::cmpId (see ecs.h). This
 * how we assign numeric identifiers to components (so we can
 * easily put them in an array). The list of possible identifiers
 * is defined as an enum in ecs.h
 *
 * We use a struct to emphasise that it is actually a data structure
 * in ECS, and also to have default visibility as public.
 *
 * In principle, we don't need the methods update/render because one of the
 * reasons to use system is to avoid calling these virtual methods. Nevertheless,
 * we leave them to allow using this version of ecs without systems as well.
 *
 */
struct Component {
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
	inline void setContext(Entity *ent, Manager *mngr) {
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

protected:
	// as mentions above, when using systems these fields are not
	// really needed, but we keep them for now from the same reason that
	// we keep update/render
	//
	entity_t ent_; // a reference to the entity, should not be deleted on destruction
	Manager *mngr_; //  a pointer to the manager, should not be deleted on destruction
};

} // end of namespace
