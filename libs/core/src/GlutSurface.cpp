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
}

void GlutSurface::surfaceIdleFunc() {
}

void GlutSurface::surfaceMouseFunc(int, int, int, int) {
}

void GlutSurface::surfaceKeybordFunc(unsigned char, int, int) {
}


void GlutSurface::dispaly() {

    CMDArguments& args = appListener->getCMDArgs();
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
