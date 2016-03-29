#include <core\Application.hpp>
#include <core\GlutSurface.hpp>

#include <GL\freeglut.h>


GlutSurface::GlutSurface(Application* app) :
    Surface(app) {
}

GlutSurface::~GlutSurface() {

}

void GlutSurface::dispaly() {
    CmdArgs& args = appListener->getCMDArgs();
    glutInit(&args.argc, args.argv);
}
