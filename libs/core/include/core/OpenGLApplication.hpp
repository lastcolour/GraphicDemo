// author: Oleksii Zhogan

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
    GLuint loadOpenGLProgram(const char* vertShader, const char* fragShader);
    GLuint loadOpenGLProgram(GLuint vertShader, GLuint fragShader);

    int run();

private:

    Surface* surfaceImpl;
    ResourceManager* resourceImpl;

};

#endif /* __OPENGL_APPLICATION_HPP__*/
