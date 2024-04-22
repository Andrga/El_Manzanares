// This file is part of the course TPV2@UCM - Samir Genaim

#include "Transform.h"

#include "../sdlutils/SDLUtils.h"



void Transform::draw() {
	SDL_Renderer *renderer = sdlutils().renderer();


	// assuming the (0,0) point is the middle of the object, the following are
	// vectors to the corners of its bounding rectangle
	Vector2D lu = Vector2D(-width_ / 2.0f, -height_ / 2.0f);
	Vector2D ru = Vector2D(width_ / 2.0f, -height_ / 2.0f);
	Vector2D rb = Vector2D(width_ / 2.0f, height_ / 2.0f);
	Vector2D lb = Vector2D(-width_ / 2.0f, height_ / 2.0f);

	// rotate the corners, so we get a rotated rectangle
	lu = lu.rotate(rot_);
	ru = ru.rotate(rot_);
	rb = rb.rotate(rot_);
	lb = lb.rotate(rot_);

	// the center of the object
	float x = pos_.getX() + width_ / 2.0f;
	float y = pos_.getY() + height_ / 2.0f;

	// draw lines between the corners, after shifting them by (x,y)
	SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0x0000ff00)));
	SDL_RenderDrawLine(renderer, lu.getX() + x, lu.getY() + y, ru.getX() + x,
			ru.getY() + y);
	SDL_RenderDrawLine(renderer, ru.getX() + x, ru.getY() + y, rb.getX() + x,
			rb.getY() + y);
	SDL_RenderDrawLine(renderer, rb.getX() + x, rb.getY() + y, lb.getX() + x,
			lb.getY() + y);
	SDL_RenderDrawLine(renderer, lb.getX() + x, lb.getY() + y, lu.getX() + x,
			lu.getY() + y);

	// draw center point
	SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0xff000000)));
	SDL_Rect dest = build_sdlrect(x - 1, y - 1, 3, 3);
	SDL_RenderFillRect(renderer, &dest);

	// draw velocity vector
	SDL_SetRenderDrawColor(renderer, COLOREXP(build_sdlcolor(0x00ff0011)));

	Vector2D vel = vel_;
	float wh = std::min(height_, width_) / 2.0f; // minimum of width an height
	vel = vel * wh / 2.0f;
	SDL_RenderDrawLine(renderer, x, y, vel.getX() + x, vel.getY() + y);
}
