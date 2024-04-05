// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

namespace ecs {

Manager::Manager() :
		hdlrs_(), //
		entsByGroup_(), //
		sys_(), //
		msgs_(), //
		msgs_aux_() //
{

	// for each group we reserve space for 100 entities,
	// just to avoid resizing
	//
	for (auto &groupEntities : entsByGroup_) {
		groupEntities.reserve(100);
	}

	// allocate enough space for the messages queue,
	// just to avoid resizing
	//
	msgs_.reserve(100);
	msgs_aux_.reserve(100);
}

Manager::~Manager() {

	// delete all entities
	//
	for (auto &ents : entsByGroup_) {
		for (auto e : ents)
			delete e;
	}

	for (auto i = 0u; i < maxSystemId; i++)
		if (sys_[i] != nullptr)
			delete sys_[i];
}

void Manager::refresh() {

	// remove dead entities from the groups lists, and also those
	// do not belong to the group anymore
	for (ecs::grpId_t gId = 0; gId < ecs::maxGroupId; gId++) {
		auto &groupEntities = entsByGroup_[gId];
		groupEntities.erase(
				std::remove_if(groupEntities.begin(), groupEntities.end(),
						[](entity_t e) {
							if (e->alive_) {
								return false;
							} else {
								delete e;
								return true;
							}
						}), groupEntities.end());
	}

}

} // end of namespace
