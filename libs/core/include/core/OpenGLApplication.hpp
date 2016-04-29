// author: Oleksii Zhogan (alexzhogan@gmail.com)

#ifndef __OPENGL_APPLICATION_HPP__
#define __OPENGL_APPLICATION_HPP__

#include <openGL/openGL.hpp>
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

    void setResourceShadersDir(const char* dirPath);

    GLuint loadOpenGLShader(const char* shaderName, GLenum shaderType);
    GLuint loadOpenGLTexture(const char* textureName);

    int run();

protected:

    void checkInitErrors();
    void checkResizerrors();
    void checkKeyboardErrors();
    void checkDrawErrors();

private:

    void reportGLerrors(const char* location);

private:

    Surface* surfaceImpl;
    ResourceManager* resourceImpl;

};

#endif /* __OPENGL_APPLICATION_HPP__*/