// This file is part of the course TPV2@UCM - Samir Genaim

#include "Manager.h"

namespace ecs {

Manager::Manager() :
		hdlrs_(), //
		entsByGroup_() //
{

	// for each group we reserve space for 100 entities,
	// just to avoid copies
	//
	for (auto &groupEntities : entsByGroup_) {
		groupEntities.reserve(100);
	}
}

Manager::~Manager() {

	// delete all entities
	//
	for (auto &ents : entsByGroup_) {
		for (auto e : ents)
			delete e;
	}
}

void Manager::refresh() {

	// remove dead entities from the groups lists, and also those
	// do not belong to the group anymore
	for (ecs::grpId_t gId = 0; gId < ecs::maxGroupId; gId++) {
		auto &groupEntities = entsByGroup_[gId];
		groupEntities.erase(
				std::remove_if(groupEntities.begin(), groupEntities.end(),
						[this](Entity *e) {
							if (isAlive(e)) {
								return false;
							} else {
								delete e;
								return true;
							}
						}), groupEntities.end());
	}

}

} // end of namespace
