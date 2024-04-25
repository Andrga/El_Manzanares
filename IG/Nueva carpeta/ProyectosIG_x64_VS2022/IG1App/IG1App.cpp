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

void IG1App::mouse(int button, int state, int x, int y)
{
	mMouseCoord = glm::dvec2(x, y);
	mMouseButt = button;
}

void IG1App::motion(int x, int y)
{
	glm::dvec2 mp(mMouseCoord.x - x, mMouseCoord.y - y);
	//mp = newXY - mMouseCoord;

	if (mMouseButt == 0) { // Click izquierdo.
		mCamera->orbit(mp.x * 0.01, mp.y * 0.1);
	}
	else if (mMouseButt == 2) { // Click derecho.
		mCamera->moveLR(mp.x * 0.01);
		mCamera->moveUD(-mp.y * 0.01);
	}
	glutPostRedisplay();
}

void IG1App::mouseWheel(int n, int d, int x, int y)
{
	int teclasPulsadas = glutGetModifiers();

	if (teclasPulsadas <= 0) {
		mCamera->moveFB(d / 10);
	}
	else if (teclasPulsadas == GLUT_ACTIVE_CTRL) {
		mCamera->setScale(d);
	}

	glutPostRedisplay();
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

	scene_.init();
	scene_.addEntity(new RGBCube(100.0), 1);
	scene_.addEntity(new RGBRectangle(300.0, 200.0, 0.0), 0);
	scene_.addEntity(new RGBTriangle(50.0, 200.0, 0.0), 0);
	scene_.addEntity(new RegularPolygon(100, 200.0), 0);
	scene_.addEntity(new Ground(200.0, 200.0, 4, 4, "../bmps/baldosaC.bmp"), 2);
	scene_.addEntity(new BoxOutline(200, "../bmps/container.bmp", "../bmps/papelE.bmp"), 2);
	//scenes[2]->addEntity(new Star3D(300,12,200));
	scene_.addEntity(new Star3D(100, 8, 100, "../bmps/baldosaP.bmp"), 2); // Ejercicio28.
	scene_.addEntity(new GlassParapet(300, "../bmps/windowV.bmp"), 2); // Ejercicio31.
	scene_.addEntity(new Photo(500), 2); // Ejercicio31.

	//------Ejercicio58: granjero.
	scene_.addEntity(new Sphere(50, 1.0, 0.5, 0.0), 3);
	/*scenes[3]->addEntity(new Disk(50, 20));
	scenes[3]->addEntity(new PartialDisk(50, 50, 50, 50));
	scenes[3]->addEntity(new Cylinder(50, 0, 50));*/
	//------Ejercicio60: TIE.
	scene_.addEntity(new AdvancedTIEX_1(), 4);
	scene_.addEntity(new Sphere(200, 255, 233, 0), 4);

	mCamera->set2D();

	scene_.setScene(0);

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

	//------Ejercicio53:
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}

void
IG1App::free()
{ // release memory and resources
	delete mCamera;
	mCamera = nullptr;
	delete mViewPort;
	mViewPort = nullptr;
}

void
IG1App::display() const
{ // double buffering

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clears the back buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//------Ejercicio51:
	if (m2Vistas) {
		mViewPort->setSize(mWinW / 2, mWinH);
		mCamera->setSize(mViewPort->width(), mViewPort->height());


		mViewPort->setPos(0, 0);
		scene_.render(*mCamera); // uploads the viewport and camera to the GPU

		Camera mCamera2 = *mCamera;
		mViewPort->setPos(mWinW / 2, 0);
		mCamera2.setCenital();
		scene_.render(mCamera2); // uploads the viewport and camera to the GPU

	}
	else
	{
		mViewPort->setSize(mWinW, mWinH);
		mViewPort->setPos(0, 0);
		mCamera->setSize(mViewPort->width(), mViewPort->height());
		scene_.render(*mCamera); // uploads the viewport and camera to the GPU
	}


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
		scene_.setScene(0);
		break;
	case '1':
		scene_.setScene(1);
		break;
	case '2':
		scene_.setScene(2);
		break;
	case '3':
		scene_.setScene(3);
		break;
	case '4':
		scene_.setScene(4);
		break;
	case '5':
		scene_.setScene(5);
		break;
	case 'u':
		update();
		break;
		//------Ejercicio16:
	case 'U':
		glutIdleFunc(update);
		break;
		//------ Ejercicio 44:
	case 'p':
		mCamera->changePrj();
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		break;
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
	scene_.update();
}

void
IG1App::specialKey(int key, int x, int y)
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->pitchReal(-1); // rotates -1 on the X axis
		else
			mCamera->pitchReal(1); // rotates 1 on the X axis
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			mCamera->yawReal(1); // rotates 1 on the Y axis
		else
			mCamera->yawReal(-1); // rotate -1 on the Y axis
		break;
	case GLUT_KEY_UP:
		mCamera->rollReal(1); // rotates 1 on the Z axis
		break;
	case GLUT_KEY_DOWN:
		mCamera->rollReal(-1); // rotates -1 on the Z axis
		break;
	default:
		need_redisplay = false;
		break;
	} // switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to
	// display()
}
