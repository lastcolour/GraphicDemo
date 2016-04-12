// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GlutSurface.hpp>

#include <GL/freeglut.h>
#include <assert.h>

typedef unsigned int uint;

class GlutDataHandler {
public:
    // This data handler consitent with glut surface
    // TODO: Move to other file

    GlutDataHandler() :
        title("GlutSurfcace"),
        posX(0), posY(0),
        width(600), height(400),
        bufferMode(GLUT_SINGLE),
        colorMode(GLUT_RGB) {
    }


    void setTitle(const std::string& title) {
        this->title = title;
    }

    const char* getTitle() const {
        return title.c_str();
    }

    int getPosX() const {
        return posX;
    }

    int getPosY() const {
        return posY;
    }
   
    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    int getDisplayFlags() const {
        return colorMode | bufferMode;
    }

    void setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
        this->posX   = static_cast<int>(posX);
        this->posY   = static_cast<int>(posY);
        this->width  = static_cast<int>(width);
        this->height = static_cast<int>(height);
    }

    void setBufferMode(SurfaceBufferMode mode) {
        switch (mode)
        {
        case SurfaceBufferMode::SINGLE:
            bufferMode = GLUT_SINGLE;
            break;
        case SurfaceBufferMode::DOUBLE:
            bufferMode = GLUT_DOUBLE;
            break;
        default:
            assert(false && "Unssuported buffer mode");
            break;
        }
    }

    void setColorMode(SurfaceColorMode mode) {
        switch (mode)
        {
        case SurfaceColorMode::RGB:
            colorMode = GLUT_RGB;
            break;
        case SurfaceColorMode::RGBA:
            colorMode = GLUT_RGBA;
            break;
        default:
            assert(false && "Unssuported color mode");
            break;
        }
    }

private:

    std::string title;
    int posX;
    int posY;
    int width;
    int height;
    int colorMode;
    int bufferMode;

};

// Glut surface implementation

GlutSurface::GlutSurface(Application* app) :
    Surface(app), dataHandler(new GlutDataHandler()) {
}

GlutSurface::~GlutSurface() {
}

void GlutSurface::setTitle(const std::string& title) {
    dataHandler->setTitle(title);
}

void GlutSurface::setBufferMode(SurfaceBufferMode mode) {
    dataHandler->setBufferMode(mode);
}

void GlutSurface::setColorMode(SurfaceColorMode mode) {
    dataHandler->setColorMode(mode);
}

void GlutSurface::setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
    dataHandler->setGeometry(posX, posY, width, height);
}

void GlutSurface::surfaceResizeFunc(int width, int height) {
    getApp()->onResizeEvent(width, height);
}

void GlutSurface::surfaceDisplayFunc() {
    getApp()->onDrawEvent();
}

void GlutSurface::surfaceIdleFunc() {
    getApp()->onAnimateEvent();
}

void GlutSurface::surfaceMouseFunc(int, int, int, int) {
    getApp()->onMouseEvent();
}

void GlutSurface::surfaceKeybordFunc(unsigned char, int, int) {
    // TODO: Replace glut keyboard events to CoreLib keyboard events
    getApp()->onKeyboardEvent();
}

bool GlutSurface::initialize() {
    CMDArguments& args = getApp()->getCMDArgs();
    glutInit(&args.getArgc(), args.getArgv());
    glutInitDisplayMode(dataHandler->getDisplayFlags());
    
    // OpenGL Contex Setup
    glutInitContextVersion(3, 0); // TODO: Move data to dataHandler
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextFlags(GLUT_DEBUG); // TODO: Move data to dataHandler
    
    // Windows setup
    glutInitWindowPosition(dataHandler->getPosX(), dataHandler->getPosY());
    glutInitWindowSize(dataHandler->getWidth(), dataHandler->getHeight());
    glutCreateWindow(dataHandler->getTitle());
    
    // Callbacks setup
    glutReshapeFunc(surfaceResizeFunc);
    glutDisplayFunc(surfaceDisplayFunc);
    glutIdleFunc(surfaceIdleFunc);
    glutMouseFunc(surfaceMouseFunc);
    glutKeyboardFunc(surfaceKeybordFunc);
    return true;
}

void GlutSurface::swapBuffers() {
    glutSwapBuffers();
}

void GlutSurface::dispaly() {
    glutMainLoop();
}
