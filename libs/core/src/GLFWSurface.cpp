// author: Oleksii Zhogan

#include <core/Application.hpp>
#include <core/GLFWSurface.hpp>

#include <GLFW/glfw3.h>
#include <assert.h>

typedef unsigned int uint;

class GLFWDataHandler {
public:
    // This data handler consitent with glut surface
    // TODO: Move to other file

    GLFWDataHandler() :
        title("GlutSurfcace"),
        posX(0), posY(0),
        width(600), height(400),
        bufferMode(),
        colorMode() {
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
            break;
        case SurfaceBufferMode::DOUBLE:
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
            break;
        case SurfaceColorMode::RGBA:
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

GLFWSurface::GLFWSurface(Application* app) :
    Surface(app), dataHandler(new GLFWDataHandler()),
    inited(false) {
}

GLFWSurface::~GLFWSurface() {
    if (inited) {
        glfwTerminate();
    }
}

void GLFWSurface::setTitle(const std::string& title) {
    dataHandler->setTitle(title);
}

void GLFWSurface::setBufferMode(SurfaceBufferMode mode) {
    dataHandler->setBufferMode(mode);
}

void GLFWSurface::setColorMode(SurfaceColorMode mode) {
    dataHandler->setColorMode(mode);
}

void GLFWSurface::setGeometry(unsigned int posX, unsigned int posY, unsigned int width, unsigned int height) {
    dataHandler->setGeometry(posX, posY, width, height);
}

bool GLFWSurface::initialize() {
    return inited = GL_TRUE == glfwInit();
}

void GLFWSurface::swapBuffers() {
}

void GLFWSurface::dispaly() {
}
