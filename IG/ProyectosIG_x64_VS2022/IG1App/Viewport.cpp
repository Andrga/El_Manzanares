#include "Viewport.h"

void
Viewport::setSize(GLsizei xw, GLsizei yh)
{
	xWidth = xw;
	yHeight = yh;
}

void
Viewport::setPos(GLsizei xl, GLsizei yb)
{
	xLeft = xl;
	yBot = yb;
}

void
Viewport::upload() const
{
	glViewport(xLeft, yBot, xWidth, yHeight); // transfers viewport to the GPU
}
