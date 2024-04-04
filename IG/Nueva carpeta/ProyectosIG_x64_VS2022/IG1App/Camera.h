#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "Viewport.h"

class Camera
{
public:
	explicit Camera(Viewport* vp);
	~Camera() = default;

	// viewPort
	Viewport const& viewPort() const { return *mViewPort; };

	// view matrix
	glm::dmat4 const& viewMat() const { return mViewMat; };

	void set2D();
	void set3D();

	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::dmat4 const& projMat() const { return mProjMat; };

	// sets scene visible area size
	void setSize(GLdouble xw, GLdouble yh);
	// updates the scale factor
	void setScale(GLdouble s);

	// transfers its viewport, the view matrix and projection matrix to the GPU
	void upload() const
	{
		mViewPort->upload();
		uploadVM();
		uploadPM();
	};

	//------Ejercicio41:
	void moveLR(GLdouble cs); // A izquierda/A derecha
	void moveFB(GLdouble cs); // Adelante/Atras
	void moveUD(GLdouble cs); // Arriba/Abajo

	// ------Ejercicio 42:
	void changePrj();

	//------Ejercicio46:
	void pitchReal(GLdouble cs);
	void yawReal(GLdouble cs);
	void rollReal(GLdouble cs);

	//------Ejercicio48:
	void orbit(GLdouble incAng, GLdouble incY);

	//------Ejercicio50:
	void setCenital();

protected:
	glm::dvec3 mEye = { 0.0, 0.0, 500.0 }; // camera's position
	glm::dvec3 mLook = { 0.0, 0.0, 0.0 };  // target's position
	glm::dvec3 mUp = { 0.0, 1.0, 0.0 };    // the up vector

	//------Ejercicio48:
	GLdouble mRadio = 0, mAng = 0;



	glm::dmat4 mViewMat;   // view matrix = inverse of modeling matrix
	void uploadVM() const; // transfers viewMat to the GPU

	glm::dmat4 mProjMat;   // projection matrix
	void uploadPM() const; // transfers projMat to the GPU

	GLdouble xRight, xLeft, yTop, yBot;     // size of scene visible area
	GLdouble mNearVal = 1, mFarVal = 10000; // view volume
	GLdouble mScaleFact = 1;                // scale factor
	bool bOrto = true;
	Viewport* mViewPort; // the viewport

	void setVM();
	void setPM();
	//------Ejercicio39:
	glm::dvec3 mRight, mUpward, mFront;
	void setAxes();


};

#endif //_H_Camera_H_
