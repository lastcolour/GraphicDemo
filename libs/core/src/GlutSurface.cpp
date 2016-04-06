// author: Oleksii Zhogan

#include <core\Application.hpp>
#include <core\GlutSurface.hpp>

#include <GL\freeglut.h>

const unsigned int DEF_WIDTH = 600;
const unsigned int DEF_HEIGHT = 400;
const char* DEF_WIN_NAME = "Application";

GlutSurface::GlutSurface(Application* app) :
    Surface(app) {
}

GlutSurface::~GlutSurface() {
}

void GlutSurface::surfaceDisplayFunc() {
    getApp()->onDrawEvent();
}

void GlutSurface::surfaceIdleFunc() {
    getApp()->onAnimateEvent();
}

void GlutSurface::surfaceMouseFunc(int, int, int, int) {
    // TODO: Replace glut mouse events to CoreLib mouse events
    getApp()->onMouseEvent();
}

void GlutSurface::surfaceKeybordFunc(unsigned char, int, int) {
    // TODO: Replace glut keyboard events to CoreLib keyboard events
    getApp()->onKeyboardEvent();
}


void GlutSurface::dispaly() {

    CMDArguments& args = getApp()->getCMDArgs();
    glutInit(&args.getArgc(), args.getArgv());
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(DEF_WIDTH, DEF_HEIGHT);
    glutCreateWindow(DEF_WIN_NAME);

    glutDisplayFunc(surfaceDisplayFunc);
    glutIdleFunc(surfaceIdleFunc);
    glutMouseFunc(surfaceMouseFunc);
    glutKeyboardFunc(surfaceKeybordFunc);

    glutMainLoop();
}
