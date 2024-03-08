#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

// static single instance (singleton pattern)

IG1App IG1App::s_ig1app; // default constructor (constructor with no parameters)

void
IG1App::close()
{
	if (!mStop) { // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		mStop = true;        // main loop stopped
	}
	free();
}

void
IG1App::run() // enters the main event processing loop
{
	if (mWinId == 0) {      // if not initialized
		init();         // initialize the application
		glutMainLoop(); // enters the main event processing loop
		mStop = true;   // main loop has stopped
	}
}

void
IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();

	// create the scene after creating the context
	// allocate memory and resources
	mViewPort =
		new Viewport(mWinW, mWinH); // glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);

	scenes[0] = new Scene;
	scenes[1] = new Scene;
	scenes[2] = new Scene;

	scenes[1]->addEntity(new RGBCube(100.0));
	scenes[0]->addEntity(new RGBRectangle(300.0, 200.0, 0.0));
	scenes[0]->addEntity(new RGBTriangle(50.0, 200.0, 0.0));
	scenes[0]->addEntity(new RegularPolygon(100, 200.0));
	scenes[2]->addEntity(new Ground(200.0, 200.0, 4, 4, "../bmps/baldosaC.bmp"));
	scenes[2]->addEntity(new BoxOutline(200, "../bmps/container.bmp", "../bmps/papelE.bmp"));
	//scenes[2]->addEntity(new Star3D(300,12,200));
	scenes[2]->addEntity(new Star3D(100, 8, 100, "../bmps/baldosaP.bmp")); // Ejercicio28.
	scenes[2]->addEntity(new GlassParapet(200, "../bmps/windowV.bmp")); // Ejercicio31.
	scenes[2]->addEntity(new Photo(500)); // Ejercicio31.

	mCamera->set2D();

	for (auto e : scenes) {
		e->init();
	}
	actualscene = 2;
}

void
IG1App::iniWinOpenGL()
{ // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);                   // GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Para el blending.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);


	glutInitWindowSize(mWinW, mWinH); // window size
	// glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
		GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth
	// buffer and stencil buffer

	mWinId = glutCreateWindow(
		"IG1App"); // with its associated OpenGL context, return window's identifier

	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::free()
{ // release memory and resources
	for (auto e : scenes) {
		delete e;
	}
	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;
}

void
IG1App::display() const
{ // double buffering

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);

	scenes[actualscene]->render(*mCamera); // uploads the viewport and camera to the GPU

	glutSwapBuffers(); // swaps the front and back buffer
}

void
IG1App::resize(int newWidth, int newHeight)
{
	mWinW = newWidth;
	mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height());
}

void
IG1App::key(unsigned char key, int x, int y)
{
	bool need_redisplay = true;

	switch (key) {
	case 27:                     // Escape key
		glutLeaveMainLoop(); // stops main loop and destroy the OpenGL context
		break;
	case '+':
		mCamera->setScale(+0.01); // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01); // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case '0':
		actualscene = 0;
		break;
	case '1':
		actualscene = 1;
		break;
	case '2':
		actualscene = 2;
		break;
	case 'u':
		update();
		break;
		//------Ejercicio16:
	case 'U':
		glutIdleFunc(update);
	default:
		need_redisplay = false;
		break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}

//------Ejercicio13:
void IG1App::update() {
	//------Ejercicio16:
	scenes[actualscene]->update();
}

void
IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->pitch(-1); // rotates -1 on the X axis
		else
			mCamera->pitch(1); // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->yaw(1); // rotates 1 on the Y axis
		else
			mCamera->yaw(-1); // rotate -1 on the Y axis
		break;
	case GLUT_KEY_UP:
		mCamera->roll(1); // rotates 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		mCamera->roll(-1); // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}
