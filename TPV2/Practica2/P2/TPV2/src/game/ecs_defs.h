// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
#define _CMPS_LIST_ \
	TRANSFORM, \
	IMAGE, \
	STARMOTION, \
	POINTS, \
	LIFE_COMPONENT, \
	IMNUNE_COMPONENT,\
	GHOST_MOTION,\
	IMAGEWITHFRAMES, \
	MIRACULOUS, \
    SCORE

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	STARS,\
	GHOSTS,\
	FRUITS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
#define _SYS_LIST_ \
    STARS, \
	PACMAN, \
	RENDER, \
	GAMECTRL, \
	COLLISIONS, \
	GHOSTS, \
	FRUITS, \
	INMUNITY, \
    PUNT
