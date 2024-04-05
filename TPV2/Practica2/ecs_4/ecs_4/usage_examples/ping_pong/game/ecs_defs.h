// This file is part of the course TPV2@UCM - Samir Genaim


#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	TRANSFORM, \
	IMAGE, \
	RECTANGLEVIEWER, \
	PADDLECTRL, \
	GAMESTATE

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	PADDLES

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
	BALL

// Systems list - must have at least one element
//
#define _SYS_LIST_ \
    BALL, \
	PADDLES, \
	RENDER, \
	GAMECTRL, \
	COLLISIONS

