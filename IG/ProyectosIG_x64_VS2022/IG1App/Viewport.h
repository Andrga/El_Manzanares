#ifndef _H_Viewport_H_
#define _H_Viewport_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Viewport
{
public:
	Viewport(GLsizei xw, GLsizei yh)
	  : xWidth(xw)
	  , yHeight(yh){};
	~Viewport() = default;

	GLsizei left() const { return xLeft; };     // viewport left position
	GLsizei bot() const { return yBot; };       // viewport bottom position
	GLsizei width() const { return xWidth; };   // viewport width
	GLsizei height() const { return yHeight; }; // viewport height

	void setPos(GLsizei xl, GLsizei yb);  // sets viewport position (left and bottom)
	void setSize(GLsizei xw, GLsizei yh); // sets viewport size (width and height)

	void upload() const; // transfers viewport to the GPU

protected:
	GLint xLeft = 0, yBot = 0; // viewport's position: left and bottom
	GLsizei xWidth, yHeight;   // viewport's size: width and height
};

#endif //_H_Viewport_H_
