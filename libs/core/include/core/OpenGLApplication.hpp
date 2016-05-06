// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __OPENGL_APPLICATION_HPP__
#define __OPENGL_APPLICATION_HPP__

#include <openGL/openGL.hpp>
#include <core/Camera.hpp>
#include <core/VisualApplication.hpp>

class Surface;
class ResourceManager;

class LIB_EXPORT_CONV OpenGLApplication : public VisualApplication {
public:

    OpenGLApplication(int argc, char* argv[]);
    virtual ~OpenGLApplication();

    void setSurfaceTitle(const char* title);
    void setSurfaceGeometry(unsigned int width, unsigned int height);
    void setSurfaceResizable(bool flag);

    void surfaceSwapBuffers();

    void setOpenGLVersion(unsigned int major, unsigned int minor);
    void setOpenGLCoreProfile(bool flag);

    void setDataFolder(const char* path);

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    float getAppRunDuration() const;

    int run();

private:

    Surface* surfaceImpl;
    Camera* cameraIpml;
};

#endif /* __OPENGL_APPLICATION_HPP__*/
