// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL.h>

#include "../ecs/Component.h"

class Texture;
class Transform;

class ImageWithFrames: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::IMAGEWITHFRAMES)

	ImageWithFrames(Texture *tex, //
			int cols, int rows, //
			int x, int y, int w, int h, //
			int scol, int srow, int ncol, int nrow);
	virtual ~ImageWithFrames();
	void initComponent() override;
	void render() override;

private:
	Texture *tex_;
	Transform *tr_;
	int currFrameR_;
	int currFrameC_;
	int x_;
	int y_;
	int w_;
	int h_;
	int srow_;
	int scol_;
	int nrow_;
	int ncol_;
	int frameWidth_;
	int frameHeight_;
	Uint32 lastFrameChange_;
};

