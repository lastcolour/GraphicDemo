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

void GlutSurface::surfaceResizeFunc(int, int) {
    getApp()->onResizeEvent();
    glutSwapBuffers();
}

void GlutSurface::surfaceDisplayFunc() {
    getApp()->onDrawEvent();
    glutSwapBuffers();
}

void GlutSurface::surfaceIdleFunc() {
    //getApp()->onAnimateEvent();
    //glutSwapBuffers();
}

void GlutSurface::surfaceMouseFunc(int, int, int, int) {
    // TODO: Replace glut mouse events to CoreLib mouse events
    getApp()->onMouseEvent();
}

void GlutSurface::surfaceKeybordFunc(unsigned char, int, int) {
    // TODO: Replace glut keyboard events to CoreLib keyboard events
    getApp()->onKeyboardEvent();
}

bool GlutSurface::initialize() {
    CMDArguments& args = getApp()->getCMDArgs();
    glutInit(&args.getArgc(), args.getArgv());
    // TODO: Recive all data from internal config struct
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitContextVersion(3, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE|GLUT_DEBUG);
    glutInitWindowSize(DEF_WIDTH, DEF_HEIGHT);
    glutCreateWindow(DEF_WIN_NAME);

    glutReshapeFunc(surfaceResizeFunc);
    glutDisplayFunc(surfaceDisplayFunc);
    glutIdleFunc(surfaceIdleFunc);
    glutMouseFunc(surfaceMouseFunc);
    glutKeyboardFunc(surfaceKeybordFunc);
    return true;
}

void GlutSurface::dispaly() {
    glutMainLoop();
}
