// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "RenderComponent.h"

class ScoreRenderer: public RenderComponent {
public:
	ScoreRenderer();
	virtual ~ScoreRenderer();
	void render(Container *o) override;
};

