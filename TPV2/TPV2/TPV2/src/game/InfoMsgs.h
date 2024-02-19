// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "RenderComponent.h"

class InfoMsgs: public RenderComponent {
public:
	InfoMsgs();
	virtual ~InfoMsgs();
	void render(Container *o) override;
};

